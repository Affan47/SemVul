gx_dc_ht_binary_load(gx_device_color * pdevc, const gs_imager_state * pis,
                     gx_device * dev, gs_color_select_t select)
{
    int component_index = pdevc->colors.binary.b_index;
    const gx_ht_order *porder =
        (component_index < 0 ?
         &pdevc->colors.binary.b_ht->order :
         &pdevc->colors.binary.b_ht->components[component_index].corder);
    gx_ht_cache *pcache = porder->cache;

    if (pcache->order.bit_data != porder->bit_data)
        gx_ht_init_cache(pis->memory, pcache, porder);


    pdevc->colors.binary.b_tile = NULL;
    return 0;
}
