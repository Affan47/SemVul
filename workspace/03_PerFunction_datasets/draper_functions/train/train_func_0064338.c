epr_create_bm_eval_context(EPR_SProductId* product_id,
                                               int offset_x,
                                               int offset_y,
                                               EPR_SRaster* bitmask_raster)
{
    EPR_SBmEvalContext* context;

    context = (EPR_SBmEvalContext*) calloc(1, sizeof (EPR_SBmEvalContext));
    if (context == NULL) {
        epr_set_err(e_err_out_of_memory,
                    "epr_create_bm_eval_context: out of memory");
        return NULL;
    }
    context->product_id = product_id;
    context->offset_x = offset_x;
    context->offset_y = offset_y;
    context->bitmask_raster = bitmask_raster;
    context->flag_band_ids = epr_create_ptr_array(4);
    context->flag_rasters = epr_create_ptr_array(4);
    return context;
}
