command_realpath(char * token, Channel * c) {
    char path[FILE_PATH_SIZE];
    char * real = NULL;
    int err = 0;

    read_path(&c->inp, path, sizeof(path));
    if (read_stream(&c->inp) != 0) exception(ERR_JSON_SYNTAX);
    if (read_stream(&c->inp) != MARKER_EOM) exception(ERR_JSON_SYNTAX);

    real = canonicalize_file_name(path);
    if (real == NULL) err = errno;

    write_stringz(&c->out, "R");
    write_stringz(&c->out, token);
    write_fs_errno(&c->out, err);
    json_write_string(&c->out, real);
    write_stream(&c->out, 0);
    write_stream(&c->out, MARKER_EOM);
    free(real);
}
