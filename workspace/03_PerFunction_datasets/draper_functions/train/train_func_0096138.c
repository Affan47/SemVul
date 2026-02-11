Jim_ReaddirCmd(Jim_Interp *interp, int argc, Jim_Obj *const *argv)
{
    const char *dirPath;
    DIR *dirPtr;
    struct dirent *entryPtr;
    int nocomplain = 0;

    if (argc == 3 && Jim_CompareStringImmediate(interp, argv[1], "-nocomplain")) {
        nocomplain = 1;
    }
    if (argc != 2 && !nocomplain) {
        Jim_WrongNumArgs(interp, 1, argv, "?-nocomplain? dirPath");
        return JIM_ERR;
    }

    dirPath = Jim_String(argv[1 + nocomplain]);

    dirPtr = opendir(dirPath);
    if (dirPtr == NULL) {
        if (nocomplain) {
            return JIM_OK;
        }
        Jim_SetResultString(interp, strerror(errno), -1);
        return JIM_ERR;
    }
    Jim_SetResultString(interp, strerror(errno), -1);

    Jim_SetResult(interp, Jim_NewListObj(interp, NULL, 0));

    while ((entryPtr = readdir(dirPtr)) != NULL) {
        if (entryPtr->d_name[0] == '.') {
            if (entryPtr->d_name[1] == '\0') {
                continue;
            }
            if ((entryPtr->d_name[1] == '.') && (entryPtr->d_name[2] == '\0'))
                continue;
        }
        Jim_ListAppendElement(interp, Jim_GetResult(interp), Jim_NewStringObj(interp,
                entryPtr->d_name, -1));
    }
    closedir(dirPtr);

    return JIM_OK;
}
