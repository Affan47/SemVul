readdir_fs (struct fs_node *node, uint32_t index)
{

    if ((node->flags & 0x7) == FS_DIRECTORY && node->readdir != 0)
        return node->readdir(node, index);
    else
        return 0;
}
