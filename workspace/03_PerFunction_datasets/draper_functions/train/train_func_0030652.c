curve_samples(patch_fill_state_t *pfs,
                const gs_fixed_point *pole, int pole_step, fixed fixed_flat)
{
    curve_segment s;
    int k;

    s.p1.x = pole[pole_step].x;
    s.p1.y = pole[pole_step].y;
    s.p2.x = pole[pole_step * 2].x;
    s.p2.y = pole[pole_step * 2].y;
    s.pt.x = pole[pole_step * 3].x;
    s.pt.y = pole[pole_step * 3].y;
    k = gx_curve_log2_samples(pole[0].x, pole[0].y, &s, fixed_flat);
    {
#       if LAZY_WEDGES || QUADRANGLES
            int k1;
            fixed L = any_abs(pole[pole_step * 1].x - pole[pole_step * 0].x) + any_abs(pole[pole_step * 1].y - pole[pole_step * 0].y) +
                      any_abs(pole[pole_step * 2].x - pole[pole_step * 1].x) + any_abs(pole[pole_step * 2].y - pole[pole_step * 1].y) +
                      any_abs(pole[pole_step * 3].x - pole[pole_step * 2].x) + any_abs(pole[pole_step * 3].y - pole[pole_step * 2].y);
#       endif

#       if LAZY_WEDGES

            k1 = ilog2(L / fixed_1 / (1 << (LAZY_WEDGES_MAX_LEVEL - 1)));
            k = max(k, k1);
#       endif
#       if QUADRANGLES

            k = max(k, ilog2(L) - ilog2(pfs->max_small_coord));
#       endif
    }
    return 1 << k;
}
