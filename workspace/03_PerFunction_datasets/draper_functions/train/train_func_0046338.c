http_read(vfile *vf, char *buf, avsize_t nbyte)
{
    avssize_t res;
    struct httpfile *fil = (struct httpfile *) vf->data;
    struct sfile *sf;

    sf = http_get_serialfile(fil);
    res = av_sfile_pread(sf, buf, nbyte, vf->ptr);
    http_set_size(fil, sf);
    av_unref_obj(sf);

    if(res > 0)
        vf->ptr += res;

    return res;
}
