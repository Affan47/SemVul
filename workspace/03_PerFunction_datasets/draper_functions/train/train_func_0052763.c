devn_write_pcx_file(gx_device_printer * pdev, char * filename, int ncomp,
                            int bpc, int linesize)
{
    pcx_header header;
    int code;
    bool planar;
    char outname[gp_file_name_sizeof];
    FILE * in;
    FILE * out;
    int depth = bpc_to_depth(ncomp, bpc);

    in = gp_fopen(filename, "rb");
    if (!in)
        return_error(gs_error_invalidfileaccess);
    gs_sprintf(outname, "%s.pcx", filename);
    out = gp_fopen(outname, "wb");
    if (!out) {
        fclose(in);
        return_error(gs_error_invalidfileaccess);
    }

    planar = devn_setup_pcx_header(pdev, &header, ncomp, bpc);
    code = devn_pcx_write_page(pdev, in, linesize, out, &header, planar, depth);
    if (code >= 0)
        code = devn_finish_pcx_file(pdev, out, &header, ncomp, bpc);

    fclose(in);
    fclose(out);
    return code;
}
