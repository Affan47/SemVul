hit(const char *str,
    struct monst *mtmp,
    const char *force)
{
    if((!cansee(bhitpos.x,bhitpos.y) && !canspotmon(mtmp) &&
        !(u.uswallow && mtmp == u.ustuck))
       || !flags.verbose)
            pline("%s %s it.", The(str), vtense(str, "hit"));
    else pline("%s %s %s%s", The(str), vtense(str, "hit"),
               mon_nam(mtmp), force);
}
