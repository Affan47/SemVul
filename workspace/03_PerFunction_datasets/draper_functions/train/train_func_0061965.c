getNextNode() const
{
    DSRTreeNode *node = NULL;
    if (NodeCursor != NULL)
        return NodeCursor->Next;
    return node;
}
