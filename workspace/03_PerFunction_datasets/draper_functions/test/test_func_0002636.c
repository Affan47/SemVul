gx_dc_ht_binary_load_cache(const gx_device_color * pdevc)
{
    int component_index = pdevc->colors.binary.b_index;
    const gx_ht_order *porder =
         &pdevc->colors.binary.b_ht->components[component_index].corder;
    gx_ht_cache *pcache = porder->cache;
    int b_level = pdevc->colors.binary.b_level;
    int level = porder->levels[b_level];
    gx_ht_tile *bt;

    if (pcache->num_cached < porder->num_levels )
        bt = &pcache->ht_tiles[level / pcache->levels_per_tile];
    else
        bt =  &pcache->ht_tiles[b_level];

    if (bt->level != level) {
        int code = render_ht(bt, level, porder, pcache->base_id + b_level);

        if (code < 0)
            return_error(gs_error_Fatal);
    }
    ((gx_device_color *)pdevc)->colors.binary.b_tile = bt;
    return 0;
}
