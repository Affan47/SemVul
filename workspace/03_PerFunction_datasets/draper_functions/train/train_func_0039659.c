rb_load_internal(VALUE fname, int wrap)
{
    int state;
    rb_thread_t *th = GET_THREAD();
    volatile VALUE wrapper = th->top_wrapper;
    volatile VALUE self = th->top_self;
    volatile int loaded = FALSE;
    volatile int mild_compile_error;
#ifndef __GNUC__
    rb_thread_t *volatile th0 = th;
#endif

    th->errinfo = Qnil;

    if (!wrap) {
	rb_secure(4);
	th->top_wrapper = 0;
    }
    else {

	th->top_self = rb_obj_clone(rb_vm_top_self());
	th->top_wrapper = rb_module_new();
	rb_extend_object(th->top_self, th->top_wrapper);
    }

    mild_compile_error = th->mild_compile_error;
    PUSH_TAG();
    state = EXEC_TAG();
    if (state == 0) {
	NODE *node;
	VALUE iseq;

	th->mild_compile_error++;
	node = (NODE *)rb_load_file(RSTRING_PTR(fname));
	loaded = TRUE;
	iseq = rb_iseq_new_top(node, rb_str_new2("<top (required)>"), fname, rb_realpath_internal(Qnil, fname, 1), Qfalse);
	th->mild_compile_error--;
	rb_iseq_eval(iseq);
    }
    POP_TAG();

#ifndef __GNUC__
    th = th0;
    fname = RB_GC_GUARD(fname);
#endif
    th->mild_compile_error = mild_compile_error;
    th->top_self = self;
    th->top_wrapper = wrapper;

    if (!loaded && !FIXNUM_P(GET_THREAD()->errinfo)) {

	rb_exc_raise(GET_THREAD()->errinfo);
    }
    if (state) {
	rb_vm_jump_tag_but_local_jump(state, Qundef);
    }

    if (!NIL_P(GET_THREAD()->errinfo)) {

	rb_exc_raise(th->errinfo);
    }
}
