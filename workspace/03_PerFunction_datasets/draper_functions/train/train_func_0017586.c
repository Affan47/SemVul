calc_and_set_aligncache_size(Write_sharing *ws)
{
    int inner_size;

    inner_size = calc_inner_size(ws->parallel_section->layer_block->module,
                                 get_pointer_type_in_ps(ws->parallel_section, ws->kind, ws->entry),
                                 ws->dim);
    if (inner_size <= aligncache_tmax) {
        int aligncache_size;
        aligncache_size = lcm(inner_size, CACHE_LINE_SIZE) / inner_size;
        ws->parallel_section->layer_block->aligncache_flg = TRUE;
        ws->parallel_section->layer_block->aligncache_size
            = lcm(ws->parallel_section->layer_block->aligncache_size, aligncache_size);
    }
}
