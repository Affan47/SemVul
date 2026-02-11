CatPath(char * BasePath, const char * FilePath)
{
    int l;
    l = strlen(BasePath);

    if (FilePath[1] == ':'){

        l = 0;
    }

    if (FilePath[0] == SLASH || FilePath[0] == '.' || l == 0){

        strcpy(BasePath, FilePath);
        return;
    }

    if (BasePath[l-1] != SLASH){
        BasePath[l++] = SLASH;
        BasePath[l] = 0;
    }

    strcat(BasePath, FilePath);


}
