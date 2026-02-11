find_trap(struct trap *trap)
{
    int tt = what_trap(trap->ttyp);
    bool cleared = false;

    trap->tseen = 1;
    exercise(A_WIS, true);
    if (Blind)
    {
        feel_location(trap->tx, trap->ty);
    }
    else
    {
        newsym(trap->tx, trap->ty);
    }

    if (levl[trap->tx][trap->ty].glyph != trap_to_glyph(trap))
    {

        cls();
        map_trap(trap, 1);
        display_self();
        cleared = true;
    }

    You("find %s.", an(defsyms[trap_to_defsym(tt)].explanation));

    if (cleared)
    {
        display_nhwindow(WIN_MAP, true);
        docrt();
    }
}
