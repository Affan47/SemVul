start_tin(struct obj *otmp)
{
    int tmp;

    if (metallivorous(youmonst.data))
    {
        You("bite right into the metal tin...");
        tmp = 1;
    }
    else if (nolimbs(youmonst.data))
    {
        You("cannot handle the tin properly to open it.");
        return;
    }
    else if (otmp->blessed)
    {
        pline_The("tin opens like magic!");
        tmp = 1;
    }
    else if(uwep)
    {
        switch(uwep->otyp)
        {
        case TIN_OPENER:
            tmp = 1;
            break;
        case DAGGER:
        case SILVER_DAGGER:
        case ELVEN_DAGGER:
        case ORCISH_DAGGER:
        case ATHAME:
        case CRYSKNIFE:
            tmp = 3;
            break;
        case PICK_AXE:
        case AXE:
            tmp = 6;
            break;
        default:
            goto no_opener;
        }
        pline("Using your %s you try to open the tin.",
              aobjnam(uwep, (char *)0));
    }
    else
    {
no_opener:
        pline("It is not so easy to open this tin.");
        if(Glib)
        {
            pline_The("tin slips from your %s.",
                      makeplural(body_part(FINGER)));
            if(otmp->quan > 1L)
            {
                otmp = splitobj(otmp, 1L);
            }
            if (carried(otmp)) dropx(otmp);
            else stackobj(otmp);
            return;
        }
        tmp = rn1(1 + 500/((int)(ACURR(A_DEX) + ACURRSTR)), 10);
    }
    tin.reqtime = tmp;
    tin.usedtime = 0;
    tin.tin = otmp;
    set_occupation(opentin, "opening the tin", 0);
    return;
}
