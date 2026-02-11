epr_read_band_raster(EPR_SBandId* band_id,
                         int offset_x,
                         int offset_y,
                         EPR_SRaster* raster) {

    EPR_SProductId* product_id = NULL;
    EPR_SDatasetId* dataset_id = NULL;
    char* rec_type;

    epr_clear_err();

    if (band_id == NULL) {
        epr_set_err(e_err_invalid_band,
                    "epr_read_band_raster: band_id must not be NULL");
        return epr_get_last_err_code();
    }
    if (band_id->data_type != raster->data_type) {
        epr_set_err(e_err_illegal_data_type,
                    "epr_read_band_raster: illegal raster data type");
        return epr_get_last_err_code();
    }
    if (raster->buffer == NULL) {
        epr_set_err(e_err_illegal_arg,
                    "epr_read_band_raster: raster->buffer must not be NULL");
        return epr_get_last_err_code();
    }
    if ((offset_x<0) || (offset_y<0) || (raster->raster_width<0) || (raster->raster_height<0) || (raster->source_step_x<0) || (raster->source_step_y<0)) {
        epr_set_err(e_err_invalid_value,
                    "epr_read_band_raster: all digit parameter must be positive");
        return epr_get_last_err_code();
    }


    product_id = band_id->product_id;
    dataset_id = band_id->dataset_ref.dataset_id;
    rec_type = dataset_id->dsd->ds_type;
    if (strcmp(rec_type, "M") == 0) {
        if (epr_read_band_measurement_data(band_id,
                                           offset_x,
                                           offset_y,
                                           raster) != 0) {
            epr_set_err(e_err_file_read_error,
                        "epr_read_band_raster: unsuccessfully reading band measurement data");
            return epr_get_last_err_code();
        }
        if (band_id->bm_expr != NULL) {
            EPR_SRaster* bm_raster;
            int rd_bm;

            bm_raster = epr_create_raster(e_tid_uchar,
                                          raster->source_width,
                                          raster->source_height,
                                          raster->source_step_x,
                                          raster->source_step_y);


            rd_bm = epr_read_bitmask_raster(product_id,
                                            band_id->bm_expr,
                                            offset_x,
                                            offset_y,
                                            bm_raster);

            epr_zero_invalid_pixels(raster, bm_raster);

            epr_free_raster(bm_raster);

        }
    } else if (strcmp(rec_type, "A") == 0) {
        if (epr_read_band_annotation_data
                (band_id, offset_x, offset_y, raster)) {
            epr_set_err(e_err_file_read_error,
                        "epr_read_band_raster: unsuccessfully reading band annotation data");
            return epr_get_last_err_code();
        }
    } else {
        epr_set_err(e_err_invalid_value,
                    "epr_read_band_raster: illegat DS-TYPE; 'A' or'M' will be accepted");
        return epr_get_last_err_code();
    }
    return e_err_none;
}
