kmo_wave_guess_table_update_1 (const char *filename,
        int global_ifu_nr,  const char *filter_id,
        cpl_vector *positions, cpl_vector *lambdas) {

    cpl_table* table = NULL;
    char *coeff_cols[NR_COEFFS_COLS] = {COEFF_COLS};
    int selected_row;

    cpl_size pows[1];

    KMO_TRY
    {


cpl_polynomial *poly = cpl_polynomial_new(1);
double *px = cpl_vector_get_data((cpl_vector*)positions);
cpl_matrix *x_matrix = cpl_matrix_wrap(1, cpl_vector_get_size(positions), px);
const cpl_boolean   sampsym     = CPL_FALSE;
cpl_size mindeg1d    = 0,
         maxdeg1d    = 3;
cpl_polynomial_fit(poly,
                   x_matrix,
                   &sampsym,
                   lambdas,
                   NULL,
                   CPL_FALSE,
                   &mindeg1d,
                   &maxdeg1d);


        table = kmo_wave_guess_table_open(filename, 1);

        selected_row = kmo_wave_guess_table_get_column(table, filter_id, global_ifu_nr);

        int ix = 0;
        for (ix = 0; ix < NR_COEFFS_COLS; ix++) {
            pows[0] = ix;
            KMO_TRY_EXIT_IF_ERROR(
                    cpl_table_set_double(table, coeff_cols[ix], selected_row,
                            cpl_polynomial_get_coeff(poly, pows)));
        }
        KMO_TRY_EXIT_IF_ERROR(
                cpl_table_fill_invalid_int(table, "IFU", -1));
        KMO_TRY_EXIT_IF_ERROR(
                cpl_table_save(table, NULL, NULL, filename, CPL_IO_CREATE));

    } KMO_CATCH {
        KMO_CATCH_MSG();
    }
    cpl_table_delete(table);

}
