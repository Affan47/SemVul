cx_tree_count(const cx_tree *tree, cxcptr key)
{

    cx_tnode *x, *y;
    cxsize count = 0;


    cx_assert(tree != NULL);
    cx_assert(key != NULL);

    x = _cx_tree_lower_bound(tree, key);
    y = _cx_tree_upper_bound(tree, key);


    while (x != y) {
        ++count;
        x = _cx_tnode_next(x);
    }

    return count;

}
