slicebefore_i(VALUE yielder, VALUE enumerator, int argc, VALUE *argv)
{
    VALUE enumerable;
    struct slicebefore_arg arg;

    enumerable = rb_ivar_get(enumerator, rb_intern("slicebefore_enumerable"));
    arg.sep_pred = rb_attr_get(enumerator, rb_intern("slicebefore_sep_pred"));
    arg.sep_pat = NIL_P(arg.sep_pred) ? rb_ivar_get(enumerator, rb_intern("slicebefore_sep_pat")) : Qnil;
    arg.state = rb_ivar_get(enumerator, rb_intern("slicebefore_initial_state"));
    arg.prev_elts = Qnil;
    arg.yielder = yielder;

    if (!NIL_P(arg.state))
        arg.state = rb_obj_dup(arg.state);

    rb_block_call(enumerable, id_each, 0, 0, slicebefore_ii, (VALUE)&arg);
    if (!NIL_P(arg.prev_elts))
        rb_funcall(arg.yielder, rb_intern("<<"), 1, arg.prev_elts);
    return Qnil;
}
