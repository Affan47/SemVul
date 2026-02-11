SFstatChar (struct stat *statBuf) {
    if (S_ISDIR (statBuf->st_mode)) {
        return '/';
    } else if (S_ISREG (statBuf->st_mode)) {
        return S_ISXXX (statBuf->st_mode) ? '*' : ' ';
#ifdef S_ISSOCK
    } else if (S_ISSOCK (statBuf->st_mode)) {
        return '=';
#endif
    } else {
        return ' ';
    }
}
