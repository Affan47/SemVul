drag_down(void)
{
    bool forward;
    uchar dragchance = 3;


    forward = carried(uball) && (uwep == uball || !uwep || !rn2(3));

    if (carried(uball)) You("lose your grip on the iron ball.");

    if (forward)
    {
        if (rn2(6))
        {
            pline_The("iron ball drags you downstairs!");
            losehp(rnd(6), "dragged downstairs by an iron ball",
                   NO_KILLER_PREFIX);
            litter();
        }
    }
    else
    {
        if (rn2(2))
        {
            pline_The("iron ball smacks into you!");
            losehp(rnd(20), "iron ball collision", KILLED_BY_AN);
            exercise(A_STR, false);
            dragchance -= 2;
        }
        if ((int) dragchance >= rnd(6))
        {
            pline_The("iron ball drags you downstairs!");
            losehp(rnd(3), "dragged downstairs by an iron ball",
                   NO_KILLER_PREFIX);
            exercise(A_STR, false);
            litter();
        }
    }
}
