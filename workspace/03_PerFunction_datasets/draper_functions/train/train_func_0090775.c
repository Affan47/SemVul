range_to_s(VALUE range)
{
    VALUE str, str2;

    str = rb_obj_as_string(RANGE_BEG(range));
    str2 = rb_obj_as_string(RANGE_END(range));
    str = rb_str_dup(str);
    rb_str_cat(str, "...", EXCL(range) ? 3 : 2);
    rb_str_append(str, str2);
    OBJ_INFECT(str, str2);

    return str;
}
