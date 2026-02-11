pkg_createSymLinks(const char *targetDir, UBool specialHandling) {
    int32_t result = 0;
    char cmd[LARGE_BUFFER_MAX_SIZE];
    char name1[SMALL_BUFFER_MAX_SIZE];
    char name2[SMALL_BUFFER_MAX_SIZE];

#if defined (U_MINGW)

    return result;
#endif

#ifndef USING_CYGWIN

    if (uprv_strlen(libFileNames[LIB_FILE_VERSION]) == 0 || uprv_strlen(libFileNames[LIB_FILE_VERSION_MAJOR]) == 0 ||
        uprv_strcmp(libFileNames[LIB_FILE_VERSION], libFileNames[LIB_FILE_VERSION_MAJOR]) == 0) {
        return result;
    }

    sprintf(cmd, "cd %s && %s %s && %s %s %s",
            targetDir,
            RM_CMD,
            libFileNames[LIB_FILE_VERSION_MAJOR],
            LN_CMD,
            libFileNames[LIB_FILE_VERSION],
            libFileNames[LIB_FILE_VERSION_MAJOR]);
    result = runCommand(cmd);
    if (result != 0) {
        return result;
    }
#endif

    if (specialHandling) {
#ifdef U_CYGWIN
        sprintf(name1, "%s", libFileNames[LIB_FILE_CYGWIN]);
        sprintf(name2, "%s", libFileNames[LIB_FILE_CYGWIN_VERSION]);
#else
        goto normal_symlink_mode;
#endif
    } else {
normal_symlink_mode:
        sprintf(name1, "%s.%s", libFileNames[LIB_FILE], pkgDataFlags[SO_EXT]);
        sprintf(name2, "%s", libFileNames[LIB_FILE_VERSION]);
    }

    sprintf(cmd, "cd %s && %s %s && %s %s %s",
            targetDir,
            RM_CMD,
            name1,
            LN_CMD,
            name2,
            name1);

     result = runCommand(cmd);

    return result;
}
