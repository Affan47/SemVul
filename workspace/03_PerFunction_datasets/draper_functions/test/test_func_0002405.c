lame_set_force_short_blocks(lame_global_flags * gfp, int short_blocks)
{


    if (0 > short_blocks || 1 < short_blocks)
        return -1;

    if (short_blocks == 1)
        gfp->short_blocks = short_block_forced;
    else if (gfp->short_blocks == short_block_forced)
        gfp->short_blocks = short_block_allowed;

    return 0;
}
