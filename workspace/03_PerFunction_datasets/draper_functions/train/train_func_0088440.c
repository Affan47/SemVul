av_arch_create(struct archive *arch, const char *path, int flags)
{
    struct archnode *nod;
    struct entry *ent;

    ent = av_arch_resolve(arch, path, 1, flags);
    if(ent == NULL)
        return NULL;

    if(av_arch_isroot(arch, ent)) {
        av_log(AVLOG_WARNING, "Empty filename");
        av_unref_obj(ent);
        return NULL;
    }

    nod = (struct archnode *) av_namespace_get(ent);
    if(nod != NULL) {
        av_log(AVLOG_WARNING, "Entry for %s already exists", path);
        av_unref_obj(ent);
        return NULL;
    }

    av_namespace_setflags(ent, flags, 0);

    return ent;
}
