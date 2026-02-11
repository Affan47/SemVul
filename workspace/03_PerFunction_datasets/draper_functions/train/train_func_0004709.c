qfits_asciitable_field_to_string(
        const qfits_table   *   table,
        int                     col_id,
        int                     row_id,
        int                     use_zero_scale)
{
    qfits_col       *       col;
    char            *       ccol;
    int             *       icol;
    float           *       fcol;
    double          *       dcol;
    char                    ctmp[512];
    char            *       stmp;
    int                     field_size;
    void            *        field;
    int             *       selection;


    if (table->tab_t != QFITS_ASCIITABLE) return NULL;


    ctmp[0] = '\0';


    selection = qfits_calloc(table->nr, sizeof(int));
    selection[row_id] = 1;


    if ((field = qfits_query_column_data(table, col_id, selection,
                    NULL)) == NULL) return NULL;
    qfits_free(selection);


    col = table->col + col_id;


    if (col->atom_nb > ELEMENT_MAX_DISPLAY_SIZE) field_size = col->atom_nb + 1;
    else field_size = ELEMENT_MAX_DISPLAY_SIZE;
    stmp = qfits_malloc(field_size * sizeof(char));
    stmp[0] = '\0';


    switch(col->atom_type) {
        case TFITS_ASCII_TYPE_A:
            ccol = (char*)field;
            strncpy(ctmp, ccol, col->atom_nb);
            ctmp[col->atom_nb] = '\0';
            strcpy(stmp, ctmp);
            break;

        case TFITS_ASCII_TYPE_I:
            icol = (int*)field;

            if (col->zero_present && col->scale_present && use_zero_scale) {
                sprintf(stmp, "%f", (float)(col->zero +
                            (float)icol[0] * col->scale));
            } else {
                sprintf(stmp, "%d", icol[0]);
            }
            break;

        case TFITS_ASCII_TYPE_E:
        case TFITS_ASCII_TYPE_F:
            fcol = (float*)field;

            if (col->zero_present && col->scale_present && use_zero_scale) {
                sprintf(stmp, "%f", (float)(col->zero +
                            fcol[0] * col->scale));
            } else {
                sprintf(stmp, "%f", fcol[0]);
            }
            break;

        case TFITS_ASCII_TYPE_D:
            dcol = (double*)field;

            if (col->zero_present && col->scale_present && use_zero_scale) {
                sprintf(stmp, "%f", (float)(col->zero +
                        (float)dcol[0] * col->scale));
            } else {
                sprintf(stmp, "%g", dcol[0]);
            }
            break;
        default:
            qfits_warning("Type not recognized");
            break;
    }


    qfits_free(field);
    return stmp;
}
