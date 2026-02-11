ajFileValueCwd(void)
{
    char cwd[PATH_MAX+1];

    if(!getcwd(cwd,PATH_MAX))
    {
        ajStrAssignClear(&fileCwd);

        return fileCwd;
    }


    ajStrAssignC(&fileCwd, cwd);

    if(!ajStrSuffixC(fileCwd, SLASH_STRING))
        ajStrAppendC(&fileCwd, SLASH_STRING);

    return fileCwd;
}
