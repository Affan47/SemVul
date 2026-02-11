stealarm(void)
{
    struct monst *mtmp;
    struct obj *otmp;

    for(otmp = invent; otmp; otmp = otmp->nobj)
    {
        if(otmp->o_id == stealoid)
        {
            for(mtmp = fmon; mtmp; mtmp = mtmp->nmon)
            {
                if(mtmp->m_id == stealmid)
                {
                    if(DEADMONSTER(mtmp)) impossible("stealarm(): dead monster stealing");
                    if(!dmgtype(mtmp->data, AD_SITM))
                            goto botm;
                    if(otmp->unpaid)
                            subfrombill(otmp, shop_keeper(*u.ushops));
                    freeinv(otmp);
                    pline("%s steals %s!", Monnam(mtmp), doname(otmp));
                    mpickobj(mtmp,otmp);


                    monflee(mtmp, 0, false, false);
                    if (!tele_restrict(mtmp)) rloc(mtmp, false);
                    break;
                }
            }
            break;
        }
    }
botm:   stealoid = 0;
        return 0;
}
