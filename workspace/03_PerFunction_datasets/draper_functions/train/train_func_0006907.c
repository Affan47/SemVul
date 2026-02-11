avs_filetype_function(void)
{


    FILE *fp;
    unsigned long M, N;
    int read_order = 0;


    fp = loadpath_fopen(df_filename, "rb");
    if (!fp)
	os_error(NO_CARET, "Can't open data file \"%s\"", df_filename);


    if (!fread(&M, 4, 1, fp))
	os_error(NO_CARET, "Can't read first dimension in data file \"%s\"", df_filename);
    if (M > 0xFFFF)
	read_order = DF_3210;
    df_swap_bytes_by_endianess((char *) &M, read_order, 4);
    if (!fread(&N, 4, 1, fp))
	os_error(NO_CARET, "Can't read second dimension in data file \"%s\"", df_filename);
    df_swap_bytes_by_endianess((char *) &N, read_order, 4);

    fclose(fp);

    df_matrix_file = FALSE;
    df_binary_file = TRUE;

    df_bin_record[0].scan_skip[0] = 8;
    df_bin_record[0].scan_dim[0] = M;
    df_bin_record[0].scan_dim[1] = N;

    df_bin_record[0].scan_dir[0] = 1;
    df_bin_record[0].scan_dir[1] = -1;
    df_bin_record[0].scan_generate_coord = TRUE;
    df_bin_record[0].cart_scan[0] = DF_SCAN_POINT;
    df_bin_record[0].cart_scan[1] = DF_SCAN_LINE;


    df_extend_binary_columns(4);
    df_set_read_type(1, DF_UCHAR);
    df_set_read_type(2, DF_UCHAR);
    df_set_read_type(3, DF_UCHAR);
    df_set_read_type(4, DF_UCHAR);
    df_set_skip_before(1,0);

    df_no_use_specs = 4;
    use_spec[0].column = 2;
    use_spec[1].column = 3;
    use_spec[2].column = 4;
    use_spec[3].column = 1;

}
