PTR_AimTraverse (intercept_t* in)
{
    line_t*     li;
    mobj_t*     th;
    fixed_t     slope;
    fixed_t     thingtopslope;
    fixed_t     thingbottomslope;
    fixed_t     dist;

    if (in->isaline)
    {
        li = in->d.line;

        if ( !(li->flags & ML_TWOSIDED) )
            return false;


        P_LineOpening (li);

        if (openbottom >= opentop)
            return false;

        dist = FixedMul (attackrange, in->frac);


        if (li->backsector == NULL)
        {
            return false;
        }

        if (li->frontsector->floorheight != li->backsector->floorheight)
        {
            slope = FixedDiv (openbottom - shootz , dist);
            if (slope > bottomslope)
                bottomslope = slope;
        }

        if (li->frontsector->ceilingheight != li->backsector->ceilingheight)
        {
            slope = FixedDiv (opentop - shootz , dist);
            if (slope < topslope)
                topslope = slope;
        }

        if (topslope <= bottomslope)
            return false;

        return true;
    }


    th = in->d.thing;
    if (th == shootthing)
        return true;

    if (!(th->flags&MF_SHOOTABLE))
        return true;


    dist = FixedMul (attackrange, in->frac);
    thingtopslope = FixedDiv (th->z+th->height - shootz , dist);

    if (thingtopslope < bottomslope)
        return true;

    thingbottomslope = FixedDiv (th->z - shootz, dist);

    if (thingbottomslope > topslope)
        return true;


    if (thingtopslope > topslope)
        thingtopslope = topslope;

    if (thingbottomslope < bottomslope)
        thingbottomslope = bottomslope;

    aimslope = (thingtopslope+thingbottomslope)/2;
    linetarget = th;

    return false;
}
