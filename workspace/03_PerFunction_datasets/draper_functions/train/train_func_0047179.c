gsicc_create_mashed_clut(gsicc_lutatob *icc_luta2bparts,
                         icHeader *header, gx_color_lookup_table *Table,
                         const gs_color_space *pcs, gs_range *ranges,
                         unsigned char **pp_buffer_in, int *profile_size_out,
                         bool range_adjust, gs_memory_t* memory)
{
    int k;
    int code;
    gsicc_clut *clut;
    gs_matrix3 ident_matrix;
    gs_vector3 ones_vec;


    clut = (gsicc_clut*) gs_alloc_bytes(memory,sizeof(gsicc_clut),
                                "gsicc_create_mashed_clut");
    icc_luta2bparts->clut = clut;
    if ( icc_luta2bparts->num_in == 1 ) {

        clut->clut_dims[0] = DEFAULT_TABLE_GRAYSIZE;
    } else {
        for (k = 0; k < icc_luta2bparts->num_in; k++) {
            if (Table != NULL && Table->dims[k] > DEFAULT_TABLE_NSIZE ) {


                clut->clut_dims[k] = Table->dims[k];
            } else {

                clut->clut_dims[k] = DEFAULT_TABLE_NSIZE;
            }
        }
    }
    clut->clut_num_input = icc_luta2bparts->num_in;
    clut->clut_num_output = 3;
    clut->clut_word_width = 2;
    gsicc_create_initialize_clut(clut);

    clut->data_short =
        (unsigned short*) gs_alloc_bytes(memory,
        clut->clut_num_entries*3*sizeof(unsigned short),"gsicc_create_mashed_clut");

    code = gsicc_create_clut(pcs, clut, ranges, icc_luta2bparts->white_point,
                             range_adjust, memory);


    gs_free_object(memory, icc_luta2bparts->a_curves, "gsicc_create_mashed_clut");
    icc_luta2bparts->a_curves = NULL;
    icc_luta2bparts->b_curves = NULL;
    icc_luta2bparts->m_curves = NULL;
    ones_vec.u = 1;
    ones_vec.v = 1;
    ones_vec.w = 1;
    gsicc_make_diag_matrix(&ident_matrix,&ones_vec);
    icc_luta2bparts->matrix = &ident_matrix;

    if (icc_luta2bparts->num_in == 1 ) {
        create_lutAtoBprofile(pp_buffer_in, header, icc_luta2bparts, true, memory);
    } else {
        create_lutAtoBprofile(pp_buffer_in, header, icc_luta2bparts, false, memory);
    }

}
