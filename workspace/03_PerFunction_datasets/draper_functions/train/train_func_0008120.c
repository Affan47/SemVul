lame_set_force_ms(lame_global_flags * gfp, int force_ms)
{
    if (is_lame_global_flags_valid(gfp)) {


        if (0 > force_ms || 1 < force_ms)
            return -1;
        gfp->force_ms = force_ms;
        return 0;
    }
    return -1;
}
