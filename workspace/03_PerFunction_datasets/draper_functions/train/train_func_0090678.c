poly_level_do_with_mask(GwyDataField *dfield,
                        GwyDataField *mask,
                        GwyDataField *result,
                        GwyDataField *bg,
                        const PolyLevelArgs *args,
                        GtkListStore *coeffmodel)
{
    gint *term_powers;
    gdouble *coeffs;
    gint nterms, i, j, k;

    if (args->masking == GWY_MASK_IGNORE)
        mask = NULL;

    k = 0;
    if (args->independent) {
        nterms = (args->col_degree + 1)*(args->row_degree + 1);
        term_powers = g_new(gint, 2*nterms);
        for (i = 0; i <= args->col_degree; i++) {
            for (j = 0; j <= args->row_degree; j++) {
                term_powers[k++] = i;
                term_powers[k++] = j;
            }
        }
    }
    else {
        nterms = (args->max_degree + 1)*(args->max_degree + 2)/2;
        term_powers = g_new(gint, 2*nterms);
        for (i = 0; i <= args->max_degree; i++) {
            for (j = 0; j <= args->max_degree - i; j++) {
                term_powers[k++] = i;
                term_powers[k++] = j;
            }
        }
    }

    coeffs = gwy_data_field_fit_poly(dfield, mask, nterms, term_powers,
                                     args->masking == GWY_MASK_EXCLUDE, NULL);
    gwy_data_field_subtract_poly(result, nterms, term_powers, coeffs);
    gwy_data_field_data_changed(result);

    if (bg) {
        for (i = 0; i < nterms; i++) {
            coeffs[i] = -coeffs[i];
        }
        gwy_data_field_subtract_poly(bg, nterms, term_powers, coeffs);
        gwy_data_field_data_changed(bg);
    }

    if (coeffmodel) {
        GtkTreeIter iter;


        if (bg) {
            for (i = 0; i < nterms; i++)
                coeffs[i] = -coeffs[i];
        }

        gtk_list_store_clear(coeffmodel);
        for (k = 0; k < nterms; k++) {
            gtk_list_store_insert_with_values(coeffmodel, &iter, k,
                                              0, term_powers[2*k+1],
                                              1, term_powers[2*k],
                                              2, coeffs[k],
                                              -1);
        }
        convert_coefficients_to_real(dfield, coeffmodel);
    }

    g_free(coeffs);
    g_free(term_powers);
}
