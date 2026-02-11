command_get_children(char * token, Channel * c) {
    char id[256];
    pid_t pid = 0;
    pid_t parent = 0;

    json_read_string(&c->inp, id, sizeof(id));
    if (read_stream(&c->inp) != 0) exception(ERR_JSON_SYNTAX);
    if (read_stream(&c->inp) != MARKER_EOM) exception(ERR_JSON_SYNTAX);

    write_stringz(&c->out, "R");
    write_stringz(&c->out, token);

    pid = id2pid(id, &parent);

    if (parent != 0) {
        write_errno(&c->out, 0);
        write_stringz(&c->out, "null");
    }
    else {
        DIR * proc = NULL;
        char dir[FILE_PATH_SIZE];
        if (pid == 0) strcpy(dir, "/proc");
        else snprintf(dir, sizeof(dir), "/proc/%d/task", pid);
        proc = opendir(dir);
        if (proc == NULL) {
            int err = errno;
            if (pid != 0 && err == ENOENT) {
                struct stat buf;
                snprintf(dir, sizeof(dir), "/proc/%d", pid);
                if (stat(dir, &buf) == 0) {

                    err = 0;
                }
            }
            write_errno(&c->out, err);
            write_stringz(&c->out, "null");
        }
        else {
            int cnt = 0;
            write_errno(&c->out, 0);
            write_stream(&c->out, '[');
            for (;;) {
                struct dirent * ent = readdir(proc);
                if (ent == NULL) break;
                if (ent->d_name[0] >= '1' && ent->d_name[0] <= '9') {
                    if (cnt > 0) write_stream(&c->out, ',');
                    json_write_string(&c->out, pid2id(atol(ent->d_name), pid));
                    cnt++;
                }
            }
            write_stream(&c->out, ']');
            write_stream(&c->out, 0);
            closedir(proc);
        }
    }

    write_stream(&c->out, MARKER_EOM);
}
