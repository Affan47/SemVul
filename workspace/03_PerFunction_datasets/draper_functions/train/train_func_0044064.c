gs_type1_sbw(gs_type1_state * pcis, fixed lsbx, fixed lsby, fixed wx, fixed wy)
{
    if (!pcis->sb_set)
        pcis->lsb.x = lsbx, pcis->lsb.y = lsby,
            pcis->sb_set = true;
    if (!pcis->width_set)
        pcis->width.x = wx, pcis->width.y = wy,
            pcis->width_set = true;
    if_debug4('1', "[1]sb=(%g,%g) w=(%g,%g)\n",
              fixed2float(pcis->lsb.x), fixed2float(pcis->lsb.y),
              fixed2float(pcis->width.x), fixed2float(pcis->width.y));
    return 0;
}
