dountrap(void)
{
    if (near_capacity() >= HVY_ENCUMBER)
    {
        pline("You're too strained to do that.");
        return 0;
    }
    if ((nohands(youmonst.data) && !webmaker(youmonst.data)) || !youmonst.data->mmove)
    {
        pline("And just how do you expect to do that?");
        return 0;
    }
    else if (u.ustuck && sticks(youmonst.data))
    {
        pline("You'll have to let go of %s first.", mon_nam(u.ustuck));
        return 0;
    }
    if (u.ustuck || (welded(uwep) && bimanual(uwep)))
    {
        Your("%s seem to be too busy for that.",
             makeplural(body_part(HAND)));
        return 0;
    }
    return untrap(false);
}
