kill_unused_locations(struct session *ses)
{
    int i;
    int us[MAX_LOCATIONS];
    struct routenode *r;

    for (i=0;i<MAX_LOCATIONS;i++)
        us[i]=0;
    for (i=0;i<MAX_LOCATIONS;i++)
        if ((r=ses->routes[i]))
        {
            us[i]++;
            for (;r;r=r->next)
                us[r->dest]++;
        };
    for (i=0;i<MAX_LOCATIONS;i++)
        if (ses->locations[i]&&!us[i])
        {
            SFREE(ses->locations[i]);
            ses->locations[i]=0;
        }
}
