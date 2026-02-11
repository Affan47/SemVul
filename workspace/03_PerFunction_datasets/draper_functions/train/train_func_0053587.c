SearchDirectoryForIWAD(char *dir, int mask, GameMission_t *mission)
{
    char *filename;
    size_t i;

    for (i=0; i<arrlen(iwads); ++i)
    {
        if (((1 << iwads[i].mission) & mask) == 0)
        {
            continue;
        }

        filename = CheckDirectoryHasIWAD(dir, DEH_String(iwads[i].name));

        if (filename != NULL)
        {
            *mission = iwads[i].mission;

            return filename;
        }
    }

    return NULL;
}
