validate_comparison(node *tree)
{
    int pos;
    int nch = NCH(tree);
    int res = (validate_ntype(tree, comparison)
               && is_odd(nch)
               && validate_expr(CHILD(tree, 0)));

    for (pos = 1; res && (pos < nch); pos += 2)
        res = (validate_comp_op(CHILD(tree, pos))
               && validate_expr(CHILD(tree, pos + 1)));

    return (res);
}
