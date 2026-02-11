pkg_createWithAssemblyCode(const char *targetDir, const char mode, const char *gencFilePath) {
    char tempObjectFile[SMALL_BUFFER_MAX_SIZE] = "";
    char *cmd;
    int32_t result = 0;

    int32_t length = 0;


    uprv_strcpy(tempObjectFile, gencFilePath);
    tempObjectFile[uprv_strlen(tempObjectFile)-1] = 'o';

    length = uprv_strlen(pkgDataFlags[COMPILER]) + uprv_strlen(pkgDataFlags[LIBFLAGS])
                    + uprv_strlen(tempObjectFile) + uprv_strlen(gencFilePath) + BUFFER_PADDING_SIZE;

    cmd = (char *)uprv_malloc(sizeof(char) * length);
    if (cmd == NULL) {
        return -1;
    }


    sprintf(cmd, "%s %s -o %s %s",
            pkgDataFlags[COMPILER],
            pkgDataFlags[LIBFLAGS],
            tempObjectFile,
            gencFilePath);

    result = runCommand(cmd);
    uprv_free(cmd);
    if (result != 0) {
        fprintf(stderr, "Error creating with assembly code. Failed command: %s\n", cmd);
        return result;
    }

    return pkg_generateLibraryFile(targetDir, mode, tempObjectFile);
}
