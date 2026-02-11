kmclipm_priv_reconstruct_nnlut_reset_ifu (int ifu_nr) {

    int ix = ifu_nr - 1;
    strcpy(&nn_lut_timestamps[ix][0], error_timestamp);
    nn_lut_offsets[ix] = 0;
    if (nn_luts[ix] != NULL) {
        kmclipm_priv_cleanup_neighborlist(nn_luts[ix], nn_lut_grid_definition);
        nn_luts[ix] = NULL;
    }

}
