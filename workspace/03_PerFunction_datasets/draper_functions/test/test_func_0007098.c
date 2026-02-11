AddName(struct player_disk *g, int posizione)
{
    char namebuffer[60];
    char *c=namebuffer, *d=g->surname;

    *c++='-';


    if(*g->name)
    {
        if(*g->surname)
        {
            *c++=*g->name;
            *c++='.';
        }
        else
            strcpy(c, g->name);
    }


    while(*d)
    {
        *c++=toupper(*d);
        d++;
    }

    *c=0;

    if(teamsettings[posizione*2+1].Text)
        free(teamsettings[posizione*2+1].Text);

    teamsettings[posizione*2+1].Text=strdup(namebuffer);


}
