find_arrow(object *op, const char *type) {
    object *tmp = NULL;

    FOR_INV_PREPARE(op, inv)
        if (!tmp
        && inv->type == CONTAINER
        && inv->race == type
        && QUERY_FLAG(inv, FLAG_APPLIED))
            tmp = find_arrow(inv, type);
        else if (inv->type == ARROW && inv->race == type)
            return inv;
    FOR_INV_FINISH();
    return tmp;
}
