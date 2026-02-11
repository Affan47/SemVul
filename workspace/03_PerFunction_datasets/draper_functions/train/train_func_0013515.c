write_a2b0(cos_stream_t *pcstrm, const profile_table_t *pnt,
           gs_memory_t *mem, const gs_cie_common *pciec)
{
    const icc_a2b0_t *pa2b = pnt->write_data;
    const gs_color_space *pcs = pa2b->pcs;
    int ncomps = pa2b->header[8];
    int num_points = pa2b->num_points;
    int i;
#define MAX_NCOMPS 4
    static const byte v01[MAX_NCOMPS * 2 * 2] = {
        0,0, 255,255,   0,0, 255,255,   0,0, 255,255,   0,0, 255,255
    };
    gs_imager_state *pis;
    int code;


    if ((code = cos_stream_add_bytes(pcstrm, v01, ncomps * 4)) < 0
        )
        return code;


    code = gx_cie_to_xyz_alloc(&pis, pcs, mem);
    if (code < 0)
        return code;
    for (i = 0; i < pa2b->count; ++i) {
        double in[MAX_NCOMPS], xyz[3];
        byte entry[3 * 2];
        byte *p = entry;
        int n, j;

        for (n = i, j = ncomps - 1; j >= 0; --j, n /= num_points)
            in[j] = cache_arg(n % num_points, num_points - 1,
                              (pnt->ranges ? pnt->ranges + j : NULL));
        cie_to_xyz(in, xyz, pcs, pis, pciec);


#define MAX_ICC_XYZ_VALUE (1 + 32767.0/32768)
        for (j = 0; j < 3; ++j, p += 2)
            set_sample16(p, xyz[j] / MAX_ICC_XYZ_VALUE);
#undef MAX_ICC_XYZ_VALUE
        if ((code = cos_stream_add_bytes(pcstrm, entry, sizeof(entry))) < 0)
            break;
    }
    gx_cie_to_xyz_free(pis);
    if (code < 0)
        return code;


    return cos_stream_add_bytes(pcstrm, v01, 3 * 4);
}
