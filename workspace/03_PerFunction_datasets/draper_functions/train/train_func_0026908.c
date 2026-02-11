kdtree_get_splitdim(const kdtree_t* kd, int nodeid) {
    u32 tmpsplit;
    if (kd->splitdim)
        return kd->splitdim[nodeid];

    switch (kdtree_treetype(kd)) {
    case KDT_TREE_U32:
        tmpsplit = kd->split.u[nodeid];
        break;
    case KDT_TREE_U16:
        tmpsplit = kd->split.s[nodeid];
        break;
    default:
        return -1;
    }
    return tmpsplit & kd->dimmask;
}
