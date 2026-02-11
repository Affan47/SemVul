resetserver(const char *newname, int newmode, int newtime)
{
    if(m_demo) enddemoplayback();
    else enddemorecord();

    smode = newmode;
    copystring(smapname, newname);

    minremain = newtime >= 0 ? newtime : (m_teammode ? 15 : 10);
    gamemillis = 0;
    gamelimit = minremain*60000;
    arenaround = arenaroundstartmillis = 0;
    memset(&smapstats, 0, sizeof(smapstats));

    interm = nextsendscore = 0;
    lastfillup = servmillis;
    sents.shrink(0);
    if(mastermode == MM_PRIVATE)
    {
        loopv(savedscores) savedscores[i].valid = false;
    }
    else savedscores.shrink(0);
    ctfreset();

    nextmapname[0] = '\0';
    forceintermission = false;
}
