previousLeafNode() const
{
    NodeImpl *node = traversePreviousNode();
    while (node) {
        if (!node->hasChildNodes())
            return node;
        node = node->traversePreviousNode();
    }
    return 0;
}
