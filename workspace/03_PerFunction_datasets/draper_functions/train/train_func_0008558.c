strategy(struct monst *mtmp)
{
    long strat, dstrat;

    if (!is_covetous(mtmp->data) ||


        (mtmp->isshk && inhishop(mtmp)))
            return STRAT_NONE;

    switch((mtmp->mhp*3)/mtmp->mhpmax)
    {

    default:
    case 0:
        return(STRAT_HEAL);

    case 1:
        if(mtmp->data != &mons[PM_WIZARD_OF_YENDOR])
                return(STRAT_HEAL);


    case 2:	dstrat = STRAT_HEAL;
                break;

    case 3:	dstrat = STRAT_NONE;
                break;
    }

    if(flags.made_amulet)
            if((strat = target_on(M3_WANTSAMUL, mtmp)) != STRAT_NONE)
                    return(strat);

    if(u.uevent.invoked)
    {

        if((strat = target_on(M3_WANTSARTI, mtmp)) != STRAT_NONE)
                return(strat);
        if((strat = target_on(M3_WANTSBOOK, mtmp)) != STRAT_NONE)
                return(strat);
        if((strat = target_on(M3_WANTSBELL, mtmp)) != STRAT_NONE)
                return(strat);
        if((strat = target_on(M3_WANTSCAND, mtmp)) != STRAT_NONE)
                return(strat);
    }
    else
    {

        if((strat = target_on(M3_WANTSBOOK, mtmp)) != STRAT_NONE)
                return(strat);
        if((strat = target_on(M3_WANTSBELL, mtmp)) != STRAT_NONE)
                return(strat);
        if((strat = target_on(M3_WANTSCAND, mtmp)) != STRAT_NONE)
                return(strat);
        if((strat = target_on(M3_WANTSARTI, mtmp)) != STRAT_NONE)
                return(strat);
    }
    return(dstrat);
}
