dofiretrap(struct obj *box)
{
    bool see_it = !Blind;
    int num, alt;


    if ((box && !carried(box)) ? is_pool(box->ox, box->oy) : Underwater)
    {
        pline("A cascade of steamy bubbles erupts from %s!",
              the(box ? xname(box) : surface(u.ux,u.uy)));
        if (Fire_resistance) You("are uninjured.");
        else losehp(rnd(3), "boiling water", KILLED_BY);
        return;
    }
    pline("A %s %s from %s!", tower_of_flame,
          box ? "bursts" : "erupts",
          the(box ? xname(box) : surface(u.ux,u.uy)));
    if (Fire_resistance)
    {
        shieldeff(u.ux, u.uy);
        num = rn2(2);
    }
    else if (Upolyd)
    {
        num = d(2,4);
        switch (u.umonnum)
        {
        case PM_PAPER_GOLEM:   alt = u.mhmax; break;
        case PM_STRAW_GOLEM:   alt = u.mhmax / 2; break;
        case PM_WOOD_GOLEM:    alt = u.mhmax / 4; break;
        case PM_LEATHER_GOLEM: alt = u.mhmax / 8; break;
        default: alt = 0; break;
        }
        if (alt > num) num = alt;
        if (u.mhmax > mons[u.umonnum].mlevel)
                u.mhmax -= rn2(min(u.mhmax,num + 1)), flags.botl = 1;
    }
    else
    {
        num = d(2,4);
        if (u.uhpmax > u.ulevel)
                u.uhpmax -= rn2(min(u.uhpmax,num + 1)), flags.botl = 1;
    }
    if (!num)
            You("are uninjured.");
    else
            losehp(num, tower_of_flame, KILLED_BY_AN);
    burn_away_slime();

    if (burnarmor(&youmonst) || rn2(3))
    {
        destroy_item(SCROLL_CLASS, AD_FIRE);
        destroy_item(SPBOOK_CLASS, AD_FIRE);
        destroy_item(POTION_CLASS, AD_FIRE);
    }
    if (!box && burn_floor_paper(u.ux, u.uy, see_it, true) && !see_it)
            You("smell paper burning.");
    if (is_ice(u.ux, u.uy))
            melt_ice(u.ux, u.uy);
}
