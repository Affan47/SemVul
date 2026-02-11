enum_one(VALUE obj)
{
    VALUE result = Qundef;

    rb_block_call(obj, id_each, 0, 0, ENUMFUNC(one), (VALUE)&result);
    if (result == Qundef) return Qfalse;
    return result;
}
