rhk_sm4_read_spec_info(const RHKObject *obj,
                       const guchar *buffer,
                       gsize size,
                       guint nspec)
{
    enum { SPEC_INFO_SIZE = 28 };

    const guchar *p = buffer + obj->offset;
    RHKSpecInfo *spec_infos = NULL;
    guint i;

    if (obj->size != SPEC_INFO_SIZE)
        return spec_infos;
    if (obj->offset + nspec*SPEC_INFO_SIZE >= size)
        return spec_infos;

    spec_infos = g_new(RHKSpecInfo, nspec);
    for (i = 0; i < nspec; i++) {
        RHKSpecInfo *spec_info = spec_infos + i;
        spec_info->ftime = gwy_get_gfloat_le(&p);
        spec_info->x_coord = gwy_get_gfloat_le(&p);
        spec_info->y_coord = gwy_get_gfloat_le(&p);
        gwy_debug("[%u] x_coord = %g, y_coord = %g",
                  i, spec_info->x_coord, spec_info->y_coord);
        spec_info->dx = gwy_get_gfloat_le(&p);
        spec_info->dy = gwy_get_gfloat_le(&p);
        spec_info->cumulative_dx = gwy_get_gfloat_le(&p);
        spec_info->cumulative_dy = gwy_get_gfloat_le(&p);
    }
    return spec_infos;
}
