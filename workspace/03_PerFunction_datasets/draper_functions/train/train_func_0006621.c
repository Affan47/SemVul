makeFullFilename(const char *path, const char *name,
                 char *filename, int32_t capacity) {
    char *s;


    if(path!=NULL && path[0]!=0) {
        if((int32_t)(strlen(path)+1)>=capacity) {
            fprintf(stderr, "pathname too long: \"%s\"\n", path);
            exit(U_BUFFER_OVERFLOW_ERROR);
        }
        strcpy(filename, path);


        s=strchr(filename, 0);
        if(*(s-1)!=U_FILE_SEP_CHAR && *(s-1)!=U_FILE_ALT_SEP_CHAR) {
            *s++=U_FILE_SEP_CHAR;
        }
    } else {
        s=filename;
    }


    if((int32_t)((s-filename)+strlen(name))>=capacity) {
        fprintf(stderr, "path/filename too long: \"%s%s\"\n", filename, name);
        exit(U_BUFFER_OVERFLOW_ERROR);
    }
    strcpy(s, name);
    treeToPath(s);
}
