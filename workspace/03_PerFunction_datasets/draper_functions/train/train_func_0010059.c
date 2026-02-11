gstub_dis(t_gstub *gs)
{
    int refcount = --gs->gs_refcount;
    if ((!refcount) && gs->gs_which == GP_NONE)
        t_freebytes(gs, sizeof (*gs));
    else if (refcount < 0) bug("gstub_dis");
}
