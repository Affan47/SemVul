nodecmp (treenode_t** p0, treenode_t** p1)
{
    double diff = (*p0)->area - (*p1)->area;

    if (diff < 0) return 1;
    else if (diff > 0) return -1;
    else return 0;
}
