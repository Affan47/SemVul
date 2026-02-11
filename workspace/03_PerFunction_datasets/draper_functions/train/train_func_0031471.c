ucftp_lookup(ventry *ve, const char *name, void **newp)
{
    int res = 0;
    struct ucftpentry *parent = ucftp_ventry_ucftpentry(ve);
    struct ucftpentry *ent;

    if(parent == NULL) {
        struct ucftpconn *conn;

        if(ve->mnt->opts[0] != '\0')
            return -ENOENT;

        res = ucftp_get_conn(ucftp_ventry_ucftpfs(ve), name, &conn);
        if ( res < 0 )
            return res;

        ent = ucftp_get_root(conn);
        ucftp_release_conn(conn);
    }
    else {
        res = ucftp_do_lookup(ve, name, &ent);
        if(res < 0)
            return res;


        av_unref_obj(parent);
    }

    *newp = ent;

    if(ent != NULL && ent->node != NULL)
        return AV_TYPE(ent->node->st.mode);
    else
        return 0;
}
