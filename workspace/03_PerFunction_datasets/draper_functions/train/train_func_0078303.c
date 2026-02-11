build_children(struct jmt_parse *parse, ind_t k, ind_t item,
               struct jmt_visitor *visitor, int lvl, ind_t caller) {
    struct item *x = set_item(parse, k, item);
    struct lens *lens = lens_of_parse(parse, x->links->lens);
    struct array siblings;
    ind_t end = k;
    int r;

    array_init(&siblings, sizeof(ind_t));
    r = filter_siblings(visitor, lens, k, item, caller, &siblings);
    if (r < 0)
        goto error;


    for (ind_t i = siblings.used - 1; i > 0; i--) {
        ind_t lnk = *array_elem(siblings, i, ind_t);
        struct lens *sub = lens_of_parse(parse, x->links[lnk].lens);
        if (sub->recursive) {
            build_tree(parse, k, item, sub, visitor, lvl+1);
            ERR_BAIL(parse);
        } else {
            if (debugging("cf.jmt.visit"))
                build_trace("T", x->links->from_set, k, x, lvl+1);
            if (visitor->terminal != NULL) {
                (*visitor->terminal)(sub,
                                     x->links->from_set, k, visitor->data);
                ERR_BAIL(parse);
            }
        }
        k = x->links[lnk].from_set;
        item = x->links[lnk].from_item;
        x = set_item(parse, k, item);
    }
 error:
    array_release(&siblings);
    return end;
}
