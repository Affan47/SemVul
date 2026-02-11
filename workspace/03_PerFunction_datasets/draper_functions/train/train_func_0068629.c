vol_unlink(ventry *ve)
{
    struct volentry *ent = vol_ventry_volentry(ve);

    if(ent->node == NULL)
        return -ENOENT;

    if(AV_ISDIR(ent->node->st.mode))
        return -EISDIR;

    vol_unlink_node(ent);

    return 0;
}
