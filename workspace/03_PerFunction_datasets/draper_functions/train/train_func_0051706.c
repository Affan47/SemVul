findHomeDir(void)
{
    char* userHomeDir;
    int pathLen;

    userHomeDir = getenv("HOME");
    if(userHomeDir == NULL)

    {
        printWarning("failed to getenv(\"HOME\"), using \"/\" as "
                     "home directory");
        GBLuserHomeDir = (char*)malloc(2);
        if(GBLuserHomeDir == NULL)
            fatalError("findHomeDir(): malloc(2) failed");
        strcpy(GBLuserHomeDir, "/");
        return;
    }


    DIR* openDirTest;

    openDirTest = opendir(userHomeDir);
    if(openDirTest == NULL)
    {
        printf("failed to open directory described by $HOME: '%s'\n",
                                                            userHomeDir);
        GBLuserHomeDir = (char*)malloc(2);
        if(GBLuserHomeDir == NULL)
            fatalError("findHomeDir(): malloc(2) failed");
        strcpy(GBLuserHomeDir, "/");
        return;
    }

    closedir(openDirTest);


    pathLen = strlen(userHomeDir);
    if(userHomeDir[pathLen] == '/')
    {
        GBLuserHomeDir = (char*)malloc(pathLen + 1);
        if(GBLuserHomeDir == NULL)
            fatalError("findHomeDir(): malloc(pathLen + 1) failed");
        strcpy(GBLuserHomeDir, userHomeDir);
    }
    else
    {
        GBLuserHomeDir = (char*)malloc(pathLen + 2);
        if(GBLuserHomeDir == NULL)
            fatalError("findHomeDir(): malloc(pathLen + 2) failed");
        strcpy(GBLuserHomeDir, userHomeDir);
        strcat(GBLuserHomeDir, "/");
    }
}
