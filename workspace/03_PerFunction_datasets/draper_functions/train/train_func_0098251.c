gs_rectappend_compat(gs_state * pgs, const gs_rect * pr, uint count, bool clip)
{
    bool CPSI_mode = gs_currentcpsimode(pgs->memory);

    for (; count != 0; count--, pr++) {
        floatp px = pr->p.x, py = pr->p.y, qx = pr->q.x, qy = pr->q.y;
        int code;

        if (CPSI_mode) {


            if (clip) {


                if ((code = gs_moveto(pgs, qx, qy)) < 0 ||
                    (code = gs_lineto(pgs, qx, py)) < 0 ||
                    (code = gs_lineto(pgs, px, py)) < 0 ||
                    (code = gs_lineto(pgs, px, qy)) < 0 ||
                    (code = gs_closepath(pgs)) < 0
                    )
                    return code;
            } else {

                if (px > qx) {
                    px = qx; qx = pr->p.x;
                }
                if (py > qy) {
                    py = qy; qy = pr->p.y;
                }
                if ((code = gs_moveto(pgs, px, py)) < 0 ||
                    (code = gs_lineto(pgs, qx, py)) < 0 ||
                    (code = gs_lineto(pgs, qx, qy)) < 0 ||
                    (code = gs_lineto(pgs, px, qy)) < 0 ||
                    (code = gs_closepath(pgs)) < 0
                    )
                    return code;
            }
        } else {

            if ((qx >= px) != (qy >= py))
                qx = px, px = pr->q.x;
            if ((code = gs_moveto(pgs, px, py)) < 0 ||
                (code = gs_lineto(pgs, qx, py)) < 0 ||
                (code = gs_lineto(pgs, qx, qy)) < 0 ||
                (code = gs_lineto(pgs, px, qy)) < 0 ||
                (code = gs_closepath(pgs)) < 0
                )
                return code;
        }
    }
    return 0;
}
