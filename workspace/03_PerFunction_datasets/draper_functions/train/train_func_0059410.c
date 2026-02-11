merge_ranges(coord_range_list_t *pcrl, const line_list *ll, fixed y_min, fixed y_top)
{
    active_line *alp, *nlp;
    int code = 0;

    range_list_rescan(pcrl);
    for (alp = ll->x_list; alp != 0 && code >= 0; alp = nlp) {
        fixed x0 = alp->x_current, x1, xt;
        bool forth = (alp->direction == DIR_UP || !alp->fi.curve);
        fixed xe = (forth ? alp->fi.x3 : alp->fi.x0);
        fixed ye = (forth ? alp->fi.y3 : alp->fi.y0);

        nlp = alp->next;
        if (alp->start.y < y_min)
            continue;
        if (alp->monotonic_x && alp->monotonic_y && ye <= y_top) {
            vd_bar(alp->start.x, alp->start.y, alp->end.x, alp->end.y, 0, RGB(255, 0, 0));
            x1 = xe;
            if (x0 > x1)
                xt = x0, x0 = x1, x1 = xt;
            code = range_list_add(pcrl,
                                  fixed2int_pixround(x0 - ll->fo->adjust_left),
                                  fixed2int_rounded(x1 + ll->fo->adjust_right));
            alp->more_flattened = false;
        } else {
            x1 = x0;
            for (;;) {
                if (alp->end.y <= y_top)
                    xt = alp->end.x;
                else
                    xt = AL_X_AT_Y(alp, y_top);
                x0 = min(x0, xt);
                x1 = max(x1, xt);
                if (!alp->more_flattened || alp->end.y > y_top)
                    break;
                code = step_al(alp, true);
                if (code < 0)
                    return code;
                if (alp->end.y < alp->start.y) {
                    remove_al(ll, alp);
                    break;
                }
            }
            code = range_list_add(pcrl,
                                  fixed2int_pixround(x0 - ll->fo->adjust_left),
                                  fixed2int_rounded(x1 + ll->fo->adjust_right));
        }

    }
    return code;
}
