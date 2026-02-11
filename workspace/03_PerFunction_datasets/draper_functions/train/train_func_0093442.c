ST_doPaletteStuff(void)
{

    int		palette;
    byte*	pal;
    int		cnt;
    int		bzc;

    cnt = plyr->damagecount;

    if (plyr->powers[pw_strength])
    {

        bzc = 12 - (plyr->powers[pw_strength]>>6);

        if (bzc > cnt)
            cnt = bzc;
    }

    if (cnt)
    {
        palette = (cnt+7)>>3;

        if (palette >= NUMREDPALS)
            palette = NUMREDPALS-1;

        palette += STARTREDPALS;
    }

    else if (plyr->bonuscount)
    {
        palette = (plyr->bonuscount+7)>>3;

        if (palette >= NUMBONUSPALS)
            palette = NUMBONUSPALS-1;

        palette += STARTBONUSPALS;
    }


    else if ( plyr->nukagecount > 16*TICRATE ||
              (plyr->nukagecount & 8))
        palette = RADIATIONPAL;
    else
        palette = 0;


    if (palette != st_palette)
    {
        st_palette = palette;
        pal = (byte *) W_CacheLumpNum (lu_palette, PU_CACHE)+palette*768;
        I_SetPalette (pal);
    }

}
