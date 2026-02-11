GVL_draw_wire(int id)
{
    geovol *gvl;

    G_debug(3, "GVL_draw_wire(): id=%d", id);

    gvl = gvl_get_vol(id);

    if (gvl) {
	gvld_wire_vol(gvl);
    }

    return;
}
