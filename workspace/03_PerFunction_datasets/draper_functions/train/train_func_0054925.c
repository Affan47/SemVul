validate_sliceop(node *tree)
{
    int nch = NCH(tree);
    int res = ((nch == 1) || validate_numnodes(tree, 2, "sliceop"))
              && validate_ntype(tree, sliceop);
    if (!res && !PyErr_Occurred()) {
        res = validate_numnodes(tree, 1, "sliceop");
    }
    if (res)
        res = validate_colon(CHILD(tree, 0));
    if (res && (nch == 2))
        res = validate_test(CHILD(tree, 1));

    return (res);
}
