FindNearest(team_t *s,WORD x,WORD y)
{
    register int i;
    register WORD t,minv=32767;
    register player_t *n=&s->players[0],*g;

    for(i=0;i<10;i++)
    {
        g=&s->players[i];

        t=abs(g->world_x-x)+abs(g->world_y-y);

        if(t<minv&&g->Comando==NESSUN_COMANDO)
        {
            n=g;
            minv=t;
        }
    }

    return n;
}
