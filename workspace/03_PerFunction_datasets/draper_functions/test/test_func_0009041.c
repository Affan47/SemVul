zzip_inflate_init(ZZIP_FILE * fp, struct zzip_dir_hdr *hdr)
{
    int err;

    fp->method = hdr->d_compr;
    fp->restlen = hdr->d_usize;

    if (fp->method)
    {
        memset(&fp->d_stream, 0, sizeof(fp->d_stream));

        err = inflateInit2(&fp->d_stream, -MAX_WBITS);
        if (err != Z_OK)
            goto error;

        fp->crestlen = hdr->d_csize;
    }
    return 0;
  error:
    if (fp)
        zzip_file_close(fp);
    return err;
}
