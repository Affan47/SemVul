rect_get(local_rects_t * plr, os_ptr op, gs_memory_t *mem)
{
    int format, code;
    uint n, count;
    gs_rect *pr;
    double rv[4];

    switch (r_type(op)) {
        case t_array:
        case t_mixedarray:
        case t_shortarray:
        case t_string:
            code = num_array_format(op);
            if (code < 0)
                return code;
            format = code;
            count = num_array_size(op, format);
            if (count % 4)
                return_error(e_typecheck);
            count /= 4;
            break;
        default:
            code = num_params(op, 4, rv);
            if (code < 0)
                return code;
            plr->pr = plr->rl;
            plr->count = 1;
            plr->rl[0].q.x = (plr->rl[0].p.x = rv[0]) + rv[2];
            plr->rl[0].q.y = (plr->rl[0].p.y = rv[1]) + rv[3];
            return 4;
    }
    plr->count = count;
    if (count <= MAX_LOCAL_RECTS)
        pr = plr->rl;
    else {
        pr = (gs_rect *)gs_alloc_byte_array(mem, count, sizeof(gs_rect),
                                            "rect_get");
        if (pr == 0)
            return_error(e_VMerror);
    }
    plr->pr = pr;
    for (n = 0; n < count; n++, pr++) {
        ref rnum;
        int i;

        for (i = 0; i < 4; i++) {
            code = num_array_get(mem, (const ref *)op, format,
                                 (n << 2) + i, &rnum);
            switch (code) {
                case t_integer:
                    rv[i] = rnum.value.intval;
                    break;
                case t_real:
                    rv[i] = rnum.value.realval;
                    break;
                default:
                    return code;
            }
        }
        pr->q.x = (pr->p.x = rv[0]) + rv[2];
        pr->q.y = (pr->p.y = rv[1]) + rv[3];
    }
    return 1;
}
