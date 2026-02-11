rect_param(gs_rect *prect, os_ptr op)
{
    double coords[4];
    int code = num_params(op, 4, coords);

    if (code < 0)
        return code;
    prect->p.x = coords[0], prect->p.y = coords[1];
    prect->q.x = coords[2], prect->q.y = coords[3];
    return 0;
}
