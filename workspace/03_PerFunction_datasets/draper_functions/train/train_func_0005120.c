ucftp_init_ctl(struct vmodule *module, struct ucftpfs *fs)
{
    int res;
    struct namespace *ns;
    struct statefile *stf;
    struct entry *ent;
    struct avfs *avfs;

    res = av_state_new(module, "ucftp_ctl", &ns, &avfs);
    if(res < 0)
        return res;

    ent = av_namespace_lookup(ns, NULL, "password");
    AV_NEW(stf);
    stf->data = fs;
    stf->get = NULL;
    stf->set = ucftp_password_set;
    av_namespace_set(ent, stf);

    ent = av_namespace_lookup(ns, NULL, "loggedin");
    AV_NEW(stf);
    stf->data = fs;
    stf->get = ucftp_loggedin_get;
    stf->set = ucftp_loggedin_set;
    av_namespace_set(ent, stf);

    av_unref_obj(ns);

    return 0;
}
