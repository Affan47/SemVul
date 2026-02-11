H5S_hyper_iter_coords (const H5S_sel_iter_t *iter, hsize_t *coords)
{
    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(iter);
    HDassert(coords);


    if(iter->u.hyp.diminfo_valid) {

        if(iter->u.hyp.iter_rank != 0 && iter->u.hyp.iter_rank < iter->rank) {
            int u, v;


            u = (int)iter->rank - 1;
            v = (int)iter->u.hyp.iter_rank - 1;


            while(u >= 0) {
                if(iter->u.hyp.flattened[u]) {
                    int begin = u;


                    do {
                        u--;
                    } while(u >= 0 && iter->u.hyp.flattened[u]);


                    if(u < 0)
                        u = 0;


                    HDassert(v >= 0);


                    H5V_array_calc(iter->u.hyp.off[v], (unsigned)((begin - u) + 1), &(iter->dims[u]), &(coords[u]));


                    u--;
                    v--;
                }
                else {

                    while(u >= 0 && !iter->u.hyp.flattened[u]) {

                        HDassert(v >= 0);


                        coords[u] = iter->u.hyp.off[v];


                        u--;
                        v--;
                    }
                }
            }
            HDassert(v < 0);
        }
        else
            HDmemcpy(coords, iter->u.hyp.off, sizeof(hsize_t) * iter->rank);
    }
    else
        HDmemcpy(coords, iter->u.hyp.off, sizeof(hsize_t) * iter->rank);

    FUNC_LEAVE_NOAPI(SUCCEED)
}
