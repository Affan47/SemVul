enum_drop_while(VALUE obj)
{
    VALUE args[2];

    RETURN_ENUMERATOR(obj, 0, 0);
    args[0] = rb_ary_new();
    args[1] = Qfalse;
    rb_block_call(obj, id_each, 0, 0, drop_while_i, (VALUE)args);
    return args[0];
}
