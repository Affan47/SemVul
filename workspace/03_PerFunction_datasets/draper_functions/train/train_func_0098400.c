av_new_avfs(const char *name, struct ext_info *exts, int version,
                  int flags, struct vmodule *module, struct avfs **retp)
{
    int ret;
    struct avfs *avfs;

    ret = av_check_version("CoreLib", name, version, NEED_VER, AV_VER);
    if(ret < 0)
        return ret;

    AV_NEW_OBJ(avfs, free_avfs);
    AV_INITLOCK(avfs->lock);

    avfs->name = av_strdup(name);

    avfs->exts = copy_exts(exts);
    avfs->data = NULL;
    avfs->version = version;
    avfs->flags = flags;
    avfs->module = module;
    avfs->dev = av_mkdev(AVFS_MAJOR, new_minor());
    avfs->inoctr = 2;

    av_ref_obj(module);

    av_default_avfs(avfs);

    *retp = avfs;
    return 0;
}
