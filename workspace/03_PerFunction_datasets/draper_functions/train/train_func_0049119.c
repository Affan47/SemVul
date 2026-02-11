reward_untrap(struct trap *ttmp, struct monst *mtmp)
{
    if (!ttmp->madeby_u)
    {
        if (rnl(10) < 8 && !mtmp->mpeaceful &&
            !mtmp->msleeping && !mtmp->mfrozen &&
            !mindless(mtmp->data) &&
            mtmp->data->mlet != S_HUMAN)
        {
            mtmp->mpeaceful = 1;
            set_malign(mtmp);
            pline("%s is grateful.", Monnam(mtmp));
        }


        if (!rn2(3) && !rnl(8) && u.ualign.type == A_LAWFUL)
        {
            adjalign(1);
            You_feel("that you did the right thing.");
        }
    }
}
