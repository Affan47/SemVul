kdtree_leaf_right(const kdtree_t* kd, int nodeid) {
    int leafid = nodeid - kd->ninterior;
    if (kd->has_linear_lr)
        return linear_lr(kd, leafid+1) - 1;
    if (kd->lr)
        return kd->lr[leafid];
    return calculate_R(kd, leafid);
}
