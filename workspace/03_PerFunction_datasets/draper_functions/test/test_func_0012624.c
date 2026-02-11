pkg_archiveLibrary(const char *targetDir, const char *version, UBool reverseExt) {
    int32_t result = 0;
    char cmd[LARGE_BUFFER_MAX_SIZE];


    if (uprv_strcmp(pkgDataFlags[SOBJ_EXT], pkgDataFlags[SO_EXT]) != 0 && uprv_strcmp(pkgDataFlags[A_EXT], pkgDataFlags[SO_EXT]) == 0) {
        sprintf(libFileNames[LIB_FILE_VERSION], "%s%s%s.%s",
                libFileNames[LIB_FILE],
                pkgDataFlags[LIB_EXT_ORDER][0] == '.' ? "." : "",
                reverseExt ? version : pkgDataFlags[SO_EXT],
                reverseExt ? pkgDataFlags[SO_EXT] : version);

        sprintf(cmd, "%s %s %s%s %s%s",
                pkgDataFlags[AR],
                pkgDataFlags[ARFLAGS],
                targetDir,
                libFileNames[LIB_FILE_VERSION],
                targetDir,
                libFileNames[LIB_FILE_VERSION_TMP]);

        result = runCommand(cmd);
        if (result != 0) {
            return result;
        }

        sprintf(cmd, "%s %s%s",
            pkgDataFlags[RANLIB],
            targetDir,
            libFileNames[LIB_FILE_VERSION]);

        result = runCommand(cmd);
        if (result != 0) {
            return result;
        }


        sprintf(cmd, "%s %s%s",
                RM_CMD,
                targetDir,
                libFileNames[LIB_FILE_VERSION_TMP]);

        result = runCommand(cmd);
        if (result != 0) {
            return result;
        }

    } else {
        uprv_strcpy(libFileNames[LIB_FILE_VERSION], libFileNames[LIB_FILE_VERSION_TMP]);
    }

    return result;
}
