ztempfile(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    const char *pstr;
    char fmode[4];
    int code = parse_file_access_string(op, fmode);
    char prefix[gp_file_name_sizeof];
    char fname[gp_file_name_sizeof];
    uint fnlen;
    FILE *sfile;
    stream *s;
    byte *buf, *sbody;

    if (code < 0)
        return code;
    strcat(fmode, gp_fmode_binary_suffix);
    if (r_has_type(op - 1, t_null))
        pstr = gp_scratch_file_name_prefix;
    else {
        uint psize;

        check_read_type(op[-1], t_string);
        psize = r_size(op - 1);
        if (psize >= gp_file_name_sizeof)
            return_error(e_rangecheck);
        memcpy(prefix, op[-1].value.const_bytes, psize);
        prefix[psize] = 0;
        pstr = prefix;
    }

    if (gp_file_name_is_absolute(pstr, strlen(pstr))) {
        if (check_file_permissions(i_ctx_p, pstr, strlen(pstr),
                                   "PermitFileWriting") < 0) {
            return_error(e_invalidfileaccess);
        }
    } else if (!prefix_is_simple(pstr)) {
        return_error(e_invalidfileaccess);
    }

    s = file_alloc_stream(imemory, "ztempfile(stream)");
    if (s == 0)
        return_error(e_VMerror);
    buf = gs_alloc_bytes(imemory, file_default_buffer_size,
                         "ztempfile(buffer)");
    if (buf == 0)
        return_error(e_VMerror);
    sfile = gp_open_scratch_file(imemory, pstr, fname, fmode);
    if (sfile == 0) {
        gs_free_object(imemory, buf, "ztempfile(buffer)");
        return_error(e_invalidfileaccess);
    }
    fnlen = strlen(fname);
    sbody = ialloc_string(fnlen, ".tempfile(fname)");
    if (sbody == 0) {
        gs_free_object(imemory, buf, "ztempfile(buffer)");
        return_error(e_VMerror);
    }
    memcpy(sbody, fname, fnlen);
    file_init_stream(s, sfile, fmode, buf, file_default_buffer_size);
    code = ssetfilename(s, (const unsigned char*) fname, fnlen);
    if (code < 0) {
        gx_io_device *iodev_dflt = iodev_default(imemory);
        sclose(s);
        iodev_dflt->procs.delete_file(iodev_dflt, fname);
        ifree_string(sbody, fnlen, ".tempfile(fname)");
        return_error(e_VMerror);
    }
    make_string(op - 1, a_readonly | icurrent_space, fnlen, sbody);
    make_stream_file(op, s, fmode);
    return code;
}
