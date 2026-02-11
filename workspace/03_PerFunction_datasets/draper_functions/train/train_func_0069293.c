_get_or_create_border_extra(E_Border *bd)
{
    Border_Extra *extra;

    extra = eina_hash_find(_G.border_extras, &bd);
    if (!extra) {
        extra = E_NEW(Border_Extra, 1);
        *extra = (Border_Extra) {
            .border = bd,
            .expected = {
                .x = bd->x,
                .y = bd->y,
                .w = bd->w,
                .h = bd->h,
            },
            .orig = {
                .geom = {
                    .x = bd->x,
                    .y = bd->y,
                    .w = bd->w,
                    .h = bd->h,
                },
                .layer = bd->layer,
                .stacking = bd->client.netwm.state.stacking,
                .maximized = bd->maximized,
                .bordername = eina_stringshare_add(bd->bordername),
            },
        };
        eina_hash_direct_add(_G.border_extras, &extra->border, extra);
    } else {
        extra->expected = (geom_t) {
            .x = bd->x,
            .y = bd->y,
            .w = bd->w,
            .h = bd->h,
        };
    }

    return extra;
}
