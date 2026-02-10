UpdateKeyCfg(void)
{
    extern struct Button keycfg_bottoni[];
    int i;

    for (i = 0; i < 20; i++)
    {

        const char *tmp = SDL_GetKeyName(query[i]);
        int j = 0;
        while(*tmp)
        {
            keys_names[i][j] = toupper(*tmp);
            tmp++;
            j++;
        }
        keys_names[i][j] = 0;
        keycfg_bottoni[i * 2 + 1].Text = keys_names[i];
    }


    if (control[0] == CTRL_KEY_1)
        for (i = 16; i < 20; i++)
            keycfg_bottoni[i * 2 + 1].Text = NULL;


    if (control[1] == CTRL_KEY_1)
        for (i = 6; i < 10; i++)
            keycfg_bottoni[i * 2 + 1].Text = NULL;
}
