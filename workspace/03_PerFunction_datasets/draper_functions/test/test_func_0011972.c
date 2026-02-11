rb_get_expanded_load_path(void)
{
    VALUE load_path = rb_get_load_path();
    VALUE ary;
    long i;

    ary = rb_ary_new2(RARRAY_LEN(load_path));
    for (i = 0; i < RARRAY_LEN(load_path); ++i) {
	VALUE path = rb_file_expand_path_fast(RARRAY_PTR(load_path)[i], Qnil);
	rb_str_freeze(path);
	rb_ary_push(ary, path);
    }
    rb_obj_freeze(ary);
    return ary;
}
