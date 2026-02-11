ftwsize(const char *dir_name)
{
        DIR* dir = opendir(dir_name);
        if(dir == NULL) {
                pwarning(_("opendir on \"%s\" failed: %s"), dir_name, strerror(errno));
                return 0;
        }

        struct dirent *dirt;
        int64_t sumsize = 0;
        while(dirt = readdir(dir)) {
                if(strcmp(dirt->d_name, ".") == 0) {
                        continue;
                }
                if(strcmp(dirt->d_name, "..") == 0) {
                        continue;
                }
                char tpath[MAX_PATHLEN];
                strcpy(tpath, dir_name);
                mergepath(tpath, dirt->d_name);
                struct stat64 st;
                if(stat64(tpath, &st) == -1) {
                        continue;
                }
                if(S_ISDIR(st.st_mode)) {
                        sumsize += ftwsize(tpath);
                } else if(S_ISREG(st.st_mode)) {
                        sumsize += st.st_size;
                } else {

                }

        }
        return sumsize;
}
