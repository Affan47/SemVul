gazemm(struct monst *magr, struct monst *mdef, struct attack *mattk)
{
    char buf[BUFSZ];

    if(vis) {
        sprintf(buf,"%s gazes at", Monnam(magr));
        pline("%s %s...", buf, mon_nam(mdef));
    }

    if (magr->mcan || !magr->mcansee ||
        (magr->minvis && !perceives(mdef->data)) ||
        !mdef->mcansee || mdef->msleeping) {
        if (vis)
        {
            pline("but nothing happens.");
        }
        return(MM_MISS);
    }

    if (magr->data == &mons[PM_MEDUSA] && mon_reflects(mdef, (char *)0)) {
        if (canseemon(mdef))
                mon_reflects(mdef,
                             "The gaze is reflected away by %s %s.");
        if (mdef->mcansee) {
            if (mon_reflects(magr, (char *)0)) {
                if (canseemon(magr))
                        mon_reflects(magr,
                                     "The gaze is reflected away by %s %s.");
                return (MM_MISS);
            }
            if (mdef->minvis && !perceives(magr->data)) {
                if (canseemon(magr)) {
                    pline("%s doesn't seem to notice that %s gaze was reflected.",
                          Monnam(magr), mhis(magr));
                }
                return (MM_MISS);
            }
            if (canseemon(magr))
            {
                    pline("%s is turned to stone!", Monnam(magr));
            }
            monstone(magr);
            if (magr->mhp > 0)
            {
                return (MM_MISS);
            }
            return (MM_AGR_DIED);
        }
    }

    return(mdamagem(magr, mdef, mattk));
}
