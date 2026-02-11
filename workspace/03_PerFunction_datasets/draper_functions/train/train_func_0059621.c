Jim_fileInit(Jim_Interp *interp)
{
    if (Jim_PackageProvide(interp, "file", "1.0", JIM_ERRMSG))
        return JIM_ERR;

    Jim_CreateCommand(interp, "file", Jim_SubCmdProc, (void *)file_command_table, NULL);
    Jim_CreateCommand(interp, "pwd", Jim_PwdCmd, NULL, NULL);
    Jim_CreateCommand(interp, "cd", Jim_CdCmd, NULL, NULL);
    return JIM_OK;
}
