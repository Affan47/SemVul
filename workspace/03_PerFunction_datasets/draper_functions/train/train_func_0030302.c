print_node (trienode_t *node, char **buf)
{
        if (!node->parent)
                return;

        if (node->parent) {
                print_node (node->parent, buf);
                *(*buf)++ = node->id;
        }
}
