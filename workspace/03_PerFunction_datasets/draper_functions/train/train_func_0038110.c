read_arfile(vfile *vf, struct archive *arch)
{
    int res;
    char magic[ARMAGICLEN];
    avssize_t rres;
    struct ar_nametab nt;

    rres = av_read(vf, magic, ARMAGICLEN);
    if(rres < 0)
        return rres;
    if(rres != ARMAGICLEN || strncmp(magic, ARMAGIC, ARMAGICLEN) != 0)
        return -EIO;

    nt.names = NULL;
    nt.size = 0;
    do res = read_entry(vf, arch, &nt);
    while(res == 1);

    av_free(nt.names);

    return res;
}
