enum_find_all(VALUE obj)
{
    VALUE ary;

    RETURN_ENUMERATOR(obj, 0, 0);

    ary = rb_ary_new();
    rb_block_call(obj, id_each, 0, 0, find_all_i, ary);

    return ary;
}
