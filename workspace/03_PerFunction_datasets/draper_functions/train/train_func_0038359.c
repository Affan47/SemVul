e_missed(struct entity *etmp, bool chunks)
{
    int misses;

#ifdef D_DEBUG
    if (chunks)
    {
        pline("Do chunks miss?");
    }
#endif
    if (automiss(etmp))
    {
        return true;
    }
    if (is_flyer(etmp->edata) &&
        (is_u(etmp)? !Sleeping :
         (etmp->emon->mcanmove && !etmp->emon->msleeping)))
    {

        misses = 5;
    }
    else if (is_floater(etmp->edata) ||
             (is_u(etmp) && Levitation))
    {
        misses = 3;
    }
    else if (chunks && is_pool(etmp->ex, etmp->ey))
    {
        misses = 2;
    }
    else
    {
        misses = 0;
    }

    if (is_db_wall(etmp->ex, etmp->ey))
    {
        misses -= 3;
    }

#ifdef D_DEBUG
    pline("Miss chance = %d (out of 8)", misses);
#endif

    return ((misses >= rnd(8))? true : false);
}
