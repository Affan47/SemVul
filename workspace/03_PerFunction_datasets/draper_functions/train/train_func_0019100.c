RemoveArcadeEffect(player_t *g,UBYTE effect)
{
    switch(effect)
    {
        case ARCADE_SPEED:
            g->speed=g->OldStat;
            if(g==pl->gioc_palla)
                g->speed-=3;
            break;
        case ARCADE_FREEZE:
            {
                int i;

                g->team->ArcadeEffect=NESSUN_COMANDO;

                for(i=0;i<10;i++)
                {
                    if(g->team->players[i].ArcadeEffect==ARCADE_FREEZE)
                    {
                        g->team->players[i].Comando=NESSUN_COMANDO;
                        g->team->players[i].ArcadeEffect=NESSUN_COMANDO;
                    }
                }
            }
            break;
    }
    g->ArcadeEffect=NESSUN_COMANDO;
}
