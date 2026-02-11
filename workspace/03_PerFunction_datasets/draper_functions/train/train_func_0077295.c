insert_rarentry(struct archive *arch, struct rar_entinfo *ei)
{
    struct entry *ent;
    int entflags = 0;
    char *path = ei->name;

    dos2unix_path(path);

    if(fh_hostos(ei->fh) == OS_MSDOS) {
        conv_tolower(path);
        entflags |= NSF_NOCASE;
    }

    ent = av_arch_create(arch, path, entflags);
    if(ent == NULL)
        return;

    fill_rarentry(arch, ent, ei);
    av_unref_obj(ent);
}
