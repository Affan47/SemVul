demon_talk(struct monst *mtmp)
{
    long cash, demand, offer;

    if (uwep && uwep->oartifact == ART_EXCALIBUR)
    {
        pline("%s looks very angry.", Amonnam(mtmp));
        mtmp->mpeaceful = mtmp->mtame = 0;
        set_malign(mtmp);
        newsym(mtmp->mx, mtmp->my);
        return 0;
    }


    if (is_dprince(mtmp->data) && mtmp->minvis)
    {
        mtmp->minvis = mtmp->perminvis = 0;
        if (!Blind) pline("%s appears before you.", Amonnam(mtmp));
        newsym(mtmp->mx,mtmp->my);
    }
    if (youmonst.data->mlet == S_DEMON)
    {
        pline("%s says, \"Good hunting, %s.\"",
              Amonnam(mtmp), flags.female ? "Sister" : "Brother");
        if (!tele_restrict(mtmp)) (void) rloc(mtmp, false);
        return(1);
    }
    cash = u.ugold;
    demand = (cash * (rnd(80) + 20 * Athome)) /
        (100 * (1 + (sgn(u.ualign.type) == sgn(mtmp->data->maligntyp))));

    if (!demand)
    {
        mtmp->mpeaceful = 0;
        set_malign(mtmp);
        return 0;
    }
    else
    {


        if (mon_has_amulet(mtmp))
        {
            demand = cash + (long)rn1(1000,40);
        }

        pline("%s demands %ld %s for safe passage.",
              Amonnam(mtmp), demand, currency(demand));

        if ((offer = bribe(mtmp)) >= demand)
        {
            pline("%s vanishes, laughing about cowardly mortals.",
                  Amonnam(mtmp));
        }
        else if (offer > 0L && (long)rnd(40) > (demand - offer))
        {
            pline("%s scowls at you menacingly, then vanishes.",
                  Amonnam(mtmp));
        }
        else
        {
            pline("%s gets angry...", Amonnam(mtmp));
            mtmp->mpeaceful = 0;
            set_malign(mtmp);
            return 0;
        }
    }
    mongone(mtmp);
    return(1);
}
