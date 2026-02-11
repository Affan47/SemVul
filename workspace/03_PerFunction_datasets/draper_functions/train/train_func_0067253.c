check_do_write_array_depends(Block *a, Block *b, Statement *s)
{
    IntSet aud, abset;
    IntSet check;

    if (s->use_array_list == NULL)
        return FALSE;

    construct_IntSet(aud, range_IntSet(a->use_var_list->array_bv));
    construct_IntSet(abset, range_IntSet(a->use_var_list->array_bv));
    construct_IntSet(check, range_IntSet(a->use_var_list->array_bv));

    or_IntSet(aud, a->use_var_list->array_bv, a->def_var_list->array_bv);
    and_IntSet(abset, aud, b->def_var_list->array_bv);

    and_IntSet(check, abset, s->array_use);

    if (empty_IntSet(check)) {
        destruct_IntSet(aud);
        destruct_IntSet(abset);
        destruct_IntSet(check);
        return FALSE;
    }

    destruct_IntSet(aud);
    destruct_IntSet(abset);
    destruct_IntSet(check);

    return TRUE;
}
