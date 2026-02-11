read_bsd_longname(vfile *vf, struct archive *arch,
                             struct ar_values *arv, char *shortname)
{
    avssize_t rres;
    avsize_t namelen;
    char *name;

    namelen = getnum(shortname + 3, 13, 10);

    name = av_malloc(namelen + 1);
    rres = av_read(vf, name, namelen);
    if(rres == namelen) {
        arv->size -= namelen;
        arv->offset += namelen;

        insert_arentry(arch, arv, name);
        av_free(name);
        return 1;
    }

    av_free(name);

    if(rres < 0)
        return rres;

    av_log(AVLOG_WARNING, "AR: Broken archive");
    return 0;
}
