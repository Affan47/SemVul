check_unpaid_usage(struct obj *otmp, bool altusage)
{
    struct monst *shkp;
    const char *fmt, *arg1, *arg2;
    long tmp;

    if (!otmp->unpaid || !*u.ushops ||
        (otmp->spe <= 0 && objects[otmp->otyp].oc_charged))
            return;
    if (!(shkp = shop_keeper(*u.ushops)) || !inhishop(shkp))
            return;
    if ((tmp = cost_per_charge(shkp, otmp, altusage)) == 0L)
            return;

    arg1 = arg2 = "";
    if (otmp->oclass == SPBOOK_CLASS)
    {
        fmt = "%sYou owe%s %ld %s.";
        arg1 = rn2(2) ? "This is no free library, cad!  " : "";
        arg2 = ESHK(shkp)->debit > 0L ? " an additional" : "";
    }
    else if (otmp->otyp == POT_OIL)
    {
        fmt = "%s%sThat will cost you %ld %s (Yendorian Fuel Tax).";
    }
    else
    {
        fmt = "%s%sUsage fee, %ld %s.";
        if (!rn2(3)) arg1 = "Hey!  ";
        if (!rn2(3)) arg2 = "Ahem.  ";
    }

    if (shkp->mcanmove || !shkp->msleeping)
            verbalize(fmt, arg1, arg2, tmp, currency(tmp));
    ESHK(shkp)->debit += tmp;
    exercise(A_WIS, true);
}
