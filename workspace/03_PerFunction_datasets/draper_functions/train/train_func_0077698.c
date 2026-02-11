InitTable(void)
{
    int i,j,ns=nteams;
    char *c;

    if(turno==0)
        for(i=0;i<64;i++)
            memset(&DatiCampionato[i],0,sizeof(struct teamstats_disk));

    lb[0].ID=MENU_MATCHES;

    if(teamarray[ns-1]==FAKE_TEAM)
        ns--;

    for(j=8;j<(8*(ns+1));j+=8)
    {
        if(!league[j+1].Text)
        {
            c=(char *)malloc(54);

            for(i=0;i<7;i++)
            {
                league[j+i+1].Text=&c[i*8];
            }
        }
    }

    for(j=(8*(ns+1));j<(8*21);j+=8)
    {
        league[j].Text=NULL;

        if(league[j+1].Text)
        {
            free(league[j+1].Text);

            for(i=1;i<8;i++)
                league[j+i].Text=NULL;
        }
    }
}
