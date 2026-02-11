gsicc_create_defg_common(gs_cie_abc *pcie, gsicc_lutatob *icc_luta2bparts,
                         bool has_lmn_procs, bool has_abc_procs,
                         icHeader *header, gx_color_lookup_table *Table,
                         const gs_color_space *pcs, gs_range *ranges,
                         unsigned char **pp_buffer_in, int *profile_size_out,
                         gs_memory_t* memory)
{
    gs_matrix3 matrix_input_trans;
    int k;
    bool input_range_ok;

    gsicc_matrix_init(&(pcie->common.MatrixLMN));
    gsicc_matrix_init(&(pcie->MatrixABC));
    setheader_common(header);


    header->deviceClass = icSigInputClass;
    header->pcs = icSigXYZData;
    icc_luta2bparts->num_out = 3;
    icc_luta2bparts->white_point = &(pcie->common.points.WhitePoint);
    icc_luta2bparts->black_point = &(pcie->common.points.BlackPoint);


    if ( (!(pcie->MatrixABC.is_identity) && has_lmn_procs &&
                   !(pcie->common.MatrixLMN.is_identity)) || 1 ) {


        if (gs_color_space_get_index(pcs) == gs_color_space_index_CIEDEF) {
            input_range_ok = check_range(&(pcs->params.def->RangeDEF.ranges[0]),3);
        } else {
            input_range_ok = check_range(&(pcs->params.defg->RangeDEFG.ranges[0]),4);
        }
        gsicc_create_mashed_clut(icc_luta2bparts, header, Table,
                            pcs, ranges, pp_buffer_in, profile_size_out,
                            !input_range_ok, memory);
    } else {


        icc_luta2bparts->matrix = &matrix_input_trans;
        gsicc_create_abc_merge(icc_luta2bparts, &(pcie->common.MatrixLMN),
                                &(pcie->MatrixABC), has_abc_procs,
                                has_lmn_procs, pcie->caches.DecodeABC.caches,
                                pcie->common.caches.DecodeLMN, memory);

        icc_luta2bparts->clut = (gsicc_clut*) gs_alloc_bytes(memory,
                            sizeof(gsicc_clut),"gsicc_create_defg_common");
        for (k = 0; k < icc_luta2bparts->num_in; k++) {
            icc_luta2bparts->clut->clut_dims[k] = Table->dims[k];
        }
        icc_luta2bparts->clut->clut_num_input = icc_luta2bparts->num_in;
        icc_luta2bparts->clut->clut_num_output = 3;
        icc_luta2bparts->clut->clut_word_width = 1;
        gsicc_create_initialize_clut(icc_luta2bparts->clut);

        icc_luta2bparts->clut->data_byte = (byte*) Table->table->data;

        create_lutAtoBprofile(pp_buffer_in, header, icc_luta2bparts, false, memory);
    }
    gsicc_create_free_luta2bpart(memory, icc_luta2bparts);
    *profile_size_out = header->size;
    return(0);
}
