_clpi_parse(const char *path)
{
    BITSTREAM  bits;
    BD_FILE_H *fp;
    CLPI_CL   *cl;

    cl = calloc(1, sizeof(CLPI_CL));
    if (cl == NULL) {
        return NULL;
    }

    fp = file_open(path, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open %s\n", path);
        X_FREE(cl);
        return NULL;
    }

    bs_init(&bits, fp);
    if (!_parse_header(&bits, cl)) {
        file_close(fp);
        clpi_free(cl);
        return NULL;
    }

    if (cl->ext_data_start_addr > 0) {
        bdmv_parse_extension_data(&bits,
                                   cl->ext_data_start_addr,
                                   _parse_clpi_extension,
                                   cl);
    }

    if (!_parse_clipinfo(&bits, cl)) {
        file_close(fp);
        clpi_free(cl);
        return NULL;
    }
    if (!_parse_sequence(&bits, cl)) {
        file_close(fp);
        clpi_free(cl);
        return NULL;
    }
    if (!_parse_program_info(&bits, cl)) {
        file_close(fp);
        clpi_free(cl);
        return NULL;
    }
    if (!_parse_cpi_info(&bits, cl)) {
        file_close(fp);
        clpi_free(cl);
        return NULL;
    }
    file_close(fp);
    return cl;
}
