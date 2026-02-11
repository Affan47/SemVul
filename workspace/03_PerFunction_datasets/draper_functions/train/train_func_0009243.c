epr_create_compatible_raster(EPR_SBandId* band_id,
        uint source_width,
        uint source_height,
        uint source_step_x,
        uint source_step_y) {
    epr_clear_err();

    if (band_id == NULL) {
        epr_set_err(e_err_invalid_band, "epr_create_raster: band_id must not be NULL");
        return NULL;
    }
    return epr_create_raster(band_id->data_type,
                             source_width,
                             source_height,
                             source_step_x,
                             source_step_y);
}
