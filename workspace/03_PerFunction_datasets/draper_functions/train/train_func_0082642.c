evaluate_do(GwyNeuralNetwork *nn,
            GwyDataField *model, GwyDataField *result,
            gdouble sfactor, gdouble sshift)
{
    NeuralNetworkData *nndata = &nn->data;
    GwyDataField *scaled;
    GwySIUnit *unit;
    guint width = nndata->width, height = nndata->height, xres, yres;
    guint col, row, irow;
    const gdouble *drmodel;
    gdouble *dresult;
    gdouble avg;
    gboolean ok = FALSE;

    gwy_app_wait_set_message(_("Evaluating..."));
    gwy_app_wait_set_fraction(0.0);

    scaled = gwy_data_field_duplicate(model);
    gwy_data_field_normalize(scaled);
    xres = gwy_data_field_get_xres(scaled);
    yres = gwy_data_field_get_yres(scaled);
    drmodel = gwy_data_field_get_data_const(scaled);
    dresult = gwy_data_field_get_data(result);

    for (row = height/2; row < yres + height/2 - height; row++) {
        for (col = width/2; col < xres + width/2 - width; col++) {
            for (irow = 0; irow < height; irow++) {
                memcpy(nn->input + irow*width,
                       drmodel + ((row + irow - height/2)*xres
                                  + col - width/2),
                       width*sizeof(gdouble));
            }
            gwy_neural_network_forward_feed(nn);
            dresult[row*xres + col] = nn->output[0]/sfactor + sshift;
        }
        if (row % 32 == 31 && !gwy_app_wait_set_fraction((gdouble)row/yres))
            goto fail;
    }
    ok = TRUE;
    unit = gwy_data_field_get_si_unit_z(result);
    gwy_si_unit_set_from_string(unit, nndata->outunits);
    gwy_si_unit_power_multiply(unit, 1,
                               gwy_data_field_get_si_unit_xy(model),
                               nndata->inpowerxy,
                               unit);
    gwy_si_unit_power_multiply(unit, 1,
                               gwy_data_field_get_si_unit_z(model),
                               nndata->inpowerz,
                               unit);


    avg = gwy_data_field_area_get_avg_mask(result, NULL, GWY_MASK_IGNORE,
                                           width/2, height/2,
                                           xres - width, yres - height);
    gwy_data_field_area_fill(result, 0, 0, xres, height/2, avg);
    gwy_data_field_area_fill(result, 0, height/2, width/2, yres - height, avg);
    gwy_data_field_area_fill(result,
                             xres + width/2 - width, height/2,
                             width - width/2, yres - height,
                             avg);
    gwy_data_field_area_fill(result,
                             0, yres + height/2 - height,
                             xres, height - height/2,
                             avg);

fail:
    g_object_unref(scaled);
    return ok;
}
