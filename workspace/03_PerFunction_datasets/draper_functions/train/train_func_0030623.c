thitm(int tlev, struct monst * mon, struct obj *obj, int d_override, bool nocorpse)
{
    int strike;
    bool trapkilled = false;

    if (d_override) strike = 1;
    else if (obj) strike = (find_mac(mon) + tlev + obj->spe <= rnd(20));
    else strike = (find_mac(mon) + tlev <= rnd(20));


    if(!strike)
    {
        if (obj && cansee(mon->mx, mon->my))
                pline("%s is almost hit by %s!", Monnam(mon), doname(obj));
    }
    else
    {
        int dam = 1;

        if (obj && cansee(mon->mx, mon->my))
                pline("%s is hit by %s!", Monnam(mon), doname(obj));
        if (d_override) dam = d_override;
        else if (obj)
        {
            dam = dmgval(obj, mon);
            if (dam < 1) dam = 1;
        }
        if ((mon->mhp -= dam) <= 0)
        {
            int xx = mon->mx;
            int yy = mon->my;

            monkilled(mon, "", nocorpse ? -AD_RBRE : AD_PHYS);
            if (mon->mhp <= 0)
            {
                newsym(xx, yy);
                trapkilled = true;
            }
        }
    }
    if (obj && (!strike || d_override))
    {
        place_object(obj, mon->mx, mon->my);
        stackobj(obj);
    }
    else if (obj) dealloc_obj(obj);

    return trapkilled;
}
