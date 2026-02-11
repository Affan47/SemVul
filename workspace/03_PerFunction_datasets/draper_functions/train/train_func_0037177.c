mhurtle_step(void * arg, int x, int y)
{
    struct monst *mon = (struct monst *)arg;


    if (goodpos(x, y, mon, 0) && m_in_out_region(mon, x, y)) {
        remove_monster(mon->mx, mon->my);
        newsym(mon->mx, mon->my);
        place_monster(mon, x, y);
        newsym(mon->mx, mon->my);
        set_apparxy(mon);
        mintrap(mon);
        return true;
    }
    return false;
}
