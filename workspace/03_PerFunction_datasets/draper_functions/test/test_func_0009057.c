continue_margin_common(line_list * ll, margin_set * set, active_line * flp, active_line * alp, fixed y0, fixed y1)
{   int code;
#   if ADJUST_SERIF
    section *sect = set->sect;
    fixed yy0 = max(max(y0, alp->start.y), set->y);
    fixed yy1 = min(min(y1, alp->end.y), set->y + fixed_1);

    if (yy0 <= yy1) {
        fixed x00 = (yy0 == y0 ? flp->x_current : AL_X_AT_Y(flp, yy0));
        fixed x10 = (yy0 == y0 ? alp->x_current : AL_X_AT_Y(alp, yy0));
        fixed x01 = (yy1 == y1 ? flp->x_next : AL_X_AT_Y(flp, yy1));
        fixed x11 = (yy1 == y1 ? alp->x_next : AL_X_AT_Y(alp, yy1));
        fixed xmin = min(x00, x01), xmax = max(x10, x11);

        int i0 = fixed2int(xmin) - ll->bbox_left, i;
        int i1 = fixed2int_ceiling(xmax) - ll->bbox_left;

        for (i = i0; i < i1; i++) {
            section *s = &sect[i];
            int x_pixel = int2fixed(i + ll->bbox_left);
            int xl = max(xmin - x_pixel, 0);
            int xu = min(xmax - x_pixel, fixed_1);

            s->x0 = min(s->x0, xl);
            s->x1 = max(s->x1, xu);
            x_pixel+=0;
        }
        code = store_margin(ll, set, i0, i1);
        if (code < 0)
            return code;


    }
#   endif

    code = margin_boundary(ll, set, flp, 0, 0, yy0, yy1, 1, y0, y1);
    if (code < 0)
        return code;
    return margin_boundary(ll, set, alp, 0, 0, yy0, yy1, -1, y0, y1);
}
