fcgidsort(fcgid_procnode **e1, fcgid_procnode **e2)
{
    int cmp = strcmp((*e1)->executable_path, (*e2)->executable_path);

    if (cmp != 0)
        return cmp;
    if ((*e1)->gid != (*e2)->gid)
        return (*e1)->gid > (*e2)->gid ? 1 : -1;
    if ((*e1)->uid != (*e2)->uid)
        return (*e1)->uid > (*e2)->uid ? 1 : -1;
    cmp = strcmp((*e1)->cmdline, (*e2)->cmdline);
    if (cmp != 0)
        return cmp;
    if ((*e1)->vhost_id != (*e2)->vhost_id)
        return (*e1)->vhost_id > (*e2)->vhost_id ? 1 : -1;
    if ((*e1)->diewhy != (*e2)->diewhy)
        return (*e1)->diewhy > (*e2)->diewhy ? 1 : -1;
    if ((*e1)->node_type != (*e2)->node_type)
        return (*e1)->node_type > (*e2)->node_type ? 1 : -1;
    return 0;
}
