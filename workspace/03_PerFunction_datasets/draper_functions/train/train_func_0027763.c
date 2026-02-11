mos_apply_photometry(cpl_image *spectra, cpl_table *response,
                                cpl_table *ext_table, double startwave,
                                double dispersion, double gain,
                                double exptime, double airmass)
{
    cpl_image *extinction;
    cpl_image *outspectra;
    cpl_image *mapresponse;
    float     *res_data;
    float     *out_data;
    float     *ext_data;
    int        tlength, xlength, ylength;
    int        i, j, k;


    if (spectra == NULL || ext_table == NULL || response == NULL) {
        cpl_error_set(cpl_func, CPL_ERROR_NULL_INPUT);
        return NULL;
    }

    if (cpl_table_has_column(response, "RESPONSE")) {
        if (cpl_table_get_column_type(response, "RESPONSE") != CPL_TYPE_FLOAT) {
            cpl_table_cast_column(response, "RESPONSE", NULL, CPL_TYPE_FLOAT);
        }
        res_data = cpl_table_get_data_float(response, "RESPONSE");

        if (res_data == NULL) {
            cpl_error_set(cpl_func, CPL_ERROR_INVALID_TYPE);
            return NULL;
        }
    }
    else {
        cpl_error_set(cpl_func, CPL_ERROR_DATA_NOT_FOUND);
        return NULL;
    }

    tlength = cpl_table_get_nrow(response);
    xlength = cpl_image_get_size_x(spectra);
    ylength = cpl_image_get_size_y(spectra);

    if (xlength != tlength) {
        mapresponse = cpl_image_new(xlength, 1, CPL_TYPE_FLOAT);
        map_table(mapresponse, startwave + dispersion/2, dispersion,
                  response, "WAVE", "RESPONSE");
        res_data = cpl_image_get_data_float(mapresponse);
    }


    extinction = cpl_image_new(xlength, 1, CPL_TYPE_FLOAT);
    map_table(extinction, startwave + dispersion/2, dispersion,
              ext_table, "WAVE", "EXTINCTION");


    cpl_image_multiply_scalar(extinction, 0.4 * airmass);
    cpl_image_exponential(extinction, 10.);

    outspectra = cpl_image_duplicate(spectra);

    ext_data = cpl_image_get_data_float(extinction);
    out_data = cpl_image_get_data_float(outspectra);

    for (k = 0, i = 0; i < ylength; i++) {
        for (j = 0; j < xlength; j++, k++) {
            out_data[k] *= ext_data[j] * res_data[j];
        }
    }

    cpl_image_delete(extinction);
    if (xlength != tlength) {
        cpl_image_delete(mapresponse);
    }

    cpl_image_multiply_scalar(outspectra, gain / exptime / dispersion);

    return outspectra;
}
