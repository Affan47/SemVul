node_delete(Node *orig, u_long ind)
{
    int size = NODE_NCHILDREN(orig);
    int deletepoint = Scm__CountBitsBelow(orig->emap, ind);
    int i;


    NODE_ARC_RESET(orig, ind);
    NODE_LEAF_RESET(orig, ind);
    for (i=deletepoint; i<size-1; i++) orig->entries[i] = orig->entries[i+1];
    return size-1;
}
