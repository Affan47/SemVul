dig_up_grave(void)
{
    struct obj *otmp;


    exercise(A_WIS, false);
    if (Role_if (PM_ARCHEOLOGIST)) {
        adjalign(-sgn(u.ualign.type)*3);
        You_feel("like a despicable grave-robber!");
    } else if (Role_if (PM_SAMURAI)) {
        adjalign(-sgn(u.ualign.type));
        You("disturb the honorable dead!");
    } else if ((u.ualign.type == A_LAWFUL) && (u.ualign.record > -10)) {
        adjalign(-sgn(u.ualign.type));
        You("have violated the sanctity of this grave!");
    }

    switch (rn2(5)) {
    case 0:
    case 1:
        You("unearth a corpse.");
        if (!!(otmp = mk_tt_object(CORPSE, u.ux, u.uy)))
                otmp->age -= 100;		;
        break;
    case 2:
        if (!Blind) pline(Hallucination ? "Dude!  The living dead!" :
                          "The grave's owner is very upset!");
        makemon(mkclass(S_ZOMBIE,0), u.ux, u.uy, NO_MM_FLAGS);
        break;
    case 3:
        if (!Blind) pline(Hallucination ? "I want my mummy!" :
                          "You've disturbed a tomb!");
        makemon(mkclass(S_MUMMY,0), u.ux, u.uy, NO_MM_FLAGS);
        break;
    default:

        pline_The("grave seems unused.  Strange....");
        break;
    }
    levl[u.ux][u.uy].typ = ROOM;
    del_engr_at(u.ux, u.uy);
    newsym(u.ux,u.uy);
    return;
}
