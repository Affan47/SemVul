doswapweapon(void)
{
    register struct obj *oldwep, *oldswap;
    int result = 0;


    multi = 0;
    if (cantwield(youmonst.data))
    {
        pline("Don't be ridiculous!");
        return 0;
    }
    if (welded(uwep))
    {
        weldmsg(uwep);
        return 0;
    }


    oldwep = uwep;
    oldswap = uswapwep;
    setuswapwep(NULL);


    result = ready_weapon(oldswap);


    if (uwep == oldwep)

            setuswapwep(oldswap);
    else
    {
        setuswapwep(oldwep);
        if (uswapwep)
                prinv(NULL, uswapwep, 0L);
        else
                You("have no secondary weapon readied.");
    }

    if (u.twoweap && !can_twoweapon())
            untwoweapon();

    return (result);
}
