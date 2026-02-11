ST_loadUnloadGraphics(load_callback_t callback)
{
    int         i;
    char        namebuf[9];


    for (i=0;i<10;i++)
    {
        DEH_snprintf(namebuf, 9, "INVFONG%d", i);
        callback(namebuf, &invfontg[i]);

        DEH_snprintf(namebuf, 9, "INVFONY%d", i);
        callback(namebuf, &invfonty[i]);
    }


    if(!isdemoversion)
    {
        for(i = 0; i < 5; i++)
        {
            DEH_snprintf(namebuf, 9, "I_SGL%d", i+1);
            callback(namebuf, &invsigil[i]);
        }
    }


    for(i = 0; i < NUMAMMO; i++)
        callback(DEH_String(invammonames[i]), &invammo[i]);


    callback(DEH_String("I_ARM2"), &invarmor[0]);
    callback(DEH_String("I_ARM1"), &invarmor[1]);


    DEH_snprintf(namebuf, 9, "STBACK0%d", consoleplayer + 1);
    if(netgame)
        callback(namebuf, &stback);


    callback(DEH_String("INVBACK"),  &invback);
    callback(DEH_String("INVTOP"),   &invtop);
    callback(DEH_String("INVPOP"),   &invpop);
    callback(DEH_String("INVPOP2"),  &invpop2);
    callback(DEH_String("INVPBAK"),  &invpbak);
    callback(DEH_String("INVPBAK2"), &invpbak2);
    callback(DEH_String("INVCURS"),  &invcursor);
}
