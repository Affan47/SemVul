ucftp_mkdir(ventry *ve, avmode_t mode)
{
    int res;
    struct ucftpfs *fs = ucftp_ventry_ucftpfs(ve);
    struct ucftpentry *ent = ucftp_ventry_ucftpentry(ve);

    if(ent->node != NULL)
        return -EEXIST;

    res = ucftp_op(OP_MKD, ve);
    if(res < 0)
        return res;

    res = ucftp_make_node(fs, ent, mode | AV_IFDIR);
    if(res < 0)
        return res;

    if(ent->parent != NULL &&
       ent->parent->node != NULL)
        ent->parent->node->valid = 0;
    return 0;
}
