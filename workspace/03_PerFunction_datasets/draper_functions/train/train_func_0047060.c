kd_tree_ln_search (kd_tree_t *tree, const float *pt, unsigned *cnt)
{
    unsigned k, c = 0;
    const float *cm = tree->means;
    float d, min = l2sqr(cm, pt, tree->dim);
    cm += tree->dim;
    for (k = 1; k < tree->K; k++, cm += tree->dim) {
        d = l2sqr(cm, pt, tree->dim);
        if (d < min) {
            c = k;
            min = d;
        }
    }
    *cnt = tree->K;
    return c;
}
