initrd_finddir (struct fs_node *node, char *name)
{
    int i;

    if (node == initrd_root && !strcmp (name, "dev"))
        return initrd_dev;

    for (i = 0; i < nroot_nodes; ++i)
        if (!strcmp (name, root_nodes[i].name))
            return &root_nodes[i];

    return 0;
}
