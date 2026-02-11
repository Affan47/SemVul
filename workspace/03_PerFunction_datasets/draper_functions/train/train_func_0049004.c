OpenTeam(char *name)
{
    char path[100];
    FILE *fh;

    strcpy(path, TEMP_DIR);
    strcat(path, name);

    if(!(fh = fopen(path, "rb")))
    {
        strcpy(path, TEAMS_DIR);
        strcat(path, name);

        if(!(fh = fopen(path, "rb")))
        {
            return NULL;
        }
    }

    return fh;
}
