hitum(struct monst *mon, int tmp, struct attack *uattk)
{

    bool malive;
    int mhit = (tmp > (dieroll = rnd(20)) || u.uswallow);

    if(tmp > dieroll) exercise(A_DEX, true);
    malive = known_hitum(mon, &mhit, uattk);
    passive(mon, mhit, malive, AT_WEAP);
    return(malive);
}
