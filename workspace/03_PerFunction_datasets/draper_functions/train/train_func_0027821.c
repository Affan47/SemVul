canvas_undo_move(t_canvas *x, void *z, int action)
{
    t_undo_move *buf = z;
    if (action == UNDO_UNDO || action == UNDO_REDO)
    {
        int i;
        for (i = 0; i < buf->u_n; i++)
        {
            int x1, y1, x2, y2, newx, newy;
            t_gobj *y;
            newx = buf->u_vec[i].e_xpix;
            newy = buf->u_vec[i].e_ypix;
            y = glist_nth(x, buf->u_vec[i].e_index);
            if (y)
            {
                gobj_getrect(y, x, &x1, &y1, &x2, &y2);
                gobj_displace(y, x, newx-x1, newy - y1);
                buf->u_vec[i].e_xpix = x1;
                buf->u_vec[i].e_ypix = y1;
            }
        }
    }
    else if (action == UNDO_FREE)
    {
        t_freebytes(buf->u_vec, buf->u_n * sizeof(*buf->u_vec));
        t_freebytes(buf, sizeof(*buf));
    }
}
