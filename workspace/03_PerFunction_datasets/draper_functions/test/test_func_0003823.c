ap_just_tree_rek(AP_tree *at){
    if (at->is_leaf) return 0.0;
    double bl = ap_just_tree_rek(at->leftson);
    double br = ap_just_tree_rek(at->rightson);

    double l = at->leftlen + at->rightlen;
    double diff = fabs(bl - br);
    if (l < diff * 1.1) l = diff * 1.1;
    double go = (bl + br + l) * .5;
    at->leftlen = go - bl;
    at->rightlen = go - br;
    return go;
}
