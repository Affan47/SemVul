fill_link(struct archive *arch, struct entry *ent,
                      const char *linkname)
{
    struct entry *link;
    struct archnode *nod = NULL;

    link = av_arch_resolve(arch, linkname, 0, 0);
    if(link != NULL)
        nod = (struct archnode *) av_namespace_get(link);

    if(nod == NULL || AV_ISDIR(nod->st.mode))
        av_log(AVLOG_WARNING, "utar: Illegal hard link");
    else {
        nod->st.nlink ++;
        av_namespace_set(ent, nod);
        av_ref_obj(ent);
        av_ref_obj(nod);
    }

    av_unref_obj(link);
}
