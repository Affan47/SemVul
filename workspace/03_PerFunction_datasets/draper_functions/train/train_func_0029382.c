gs_ht_install(
                 gs_state * pgs,
                 gs_ht * pht
)
{
    int code = 0;
    gs_memory_t *pmem = pht->rc.memory;
    gx_device_halftone dev_ht;
    gx_ht_order_component *pocs;
    byte comp2order[32];
    int num_comps = pht->params.ht_multiple.num_comp;
    int i;


    if ((code = check_ht(pht)) != 0)
        return code;


    if ((pocs = alloc_ht_order(pht, pmem, comp2order)) == 0)
        return_error(gs_error_VMerror);


    for (i = 0; i < num_comps; i++) {
        int j = comp2order[i];

        code = build_component(&(pht->params.ht_multiple.components[i]),
                               &(pocs[j].corder),
                               pgs,
                               pmem
            );

        if ((code >= 0) && (j != 0)) {
            gx_ht_cache *pcache;

            pcache = gx_ht_alloc_cache(pmem,
                                       4,
                                       pocs[j].corder.raster *
                                       (pocs[j].corder.num_bits /
                                        pocs[j].corder.width) * 4
                );

            if (pcache == 0)
                code = gs_note_error(gs_error_VMerror);
            else {
                pocs[j].corder.cache = pcache;
                gx_ht_init_cache(pmem, pcache, &(pocs[j].corder));
            }
        }
        if (code < 0)
            break;
    }

    if (code < 0) {
        free_order_array(pocs, num_comps, pmem);
        return code;
    }

    dev_ht.rc.memory = pmem;
    dev_ht.order = pocs[0].corder;
    if (num_comps == 1) {

        gs_free_object(pmem, pocs, "gs_ht_install");
        dev_ht.components = 0;
    } else {
        dev_ht.components = pocs;
        dev_ht.num_comp = num_comps;
    }


    if ((code = gx_ht_install(pgs, (gs_halftone *) pht, &dev_ht)) < 0)
        gx_device_halftone_release(&dev_ht, pmem);
    return code;
}
