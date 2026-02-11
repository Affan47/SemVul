lame_set_VBR_q(lame_global_flags * gfp, int VBR_q)
{
    int     ret = 0;

    if (0 > VBR_q) {
        ret = -1;
        VBR_q = 0;
    }
    if (9 < VBR_q) {
        ret = -1;
        VBR_q = 9;
    }

    gfp->VBR_q = VBR_q;
    gfp->VBR_q_frac = 0;


    return ret;
}
