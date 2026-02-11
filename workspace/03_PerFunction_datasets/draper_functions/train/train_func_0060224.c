require_libraries(VALUE *req_list)
{
    VALUE list = *req_list;
    VALUE self = rb_vm_top_self();
    ID require;
    rb_thread_t *th = GET_THREAD();
    rb_block_t *prev_base_block = th->base_block;
    rb_encoding *extenc = rb_default_external_encoding();
    int prev_parse_in_eval = th->parse_in_eval;
    th->base_block = 0;
    th->parse_in_eval = 0;

    Init_ext();
    CONST_ID(require, "require");
    while (list && RARRAY_LEN(list) > 0) {
	VALUE feature = rb_ary_shift(list);
	rb_enc_associate(feature, extenc);
	RBASIC(feature)->klass = rb_cString;
	OBJ_FREEZE(feature);
	rb_funcall2(self, require, 1, &feature);
    }
    *req_list = 0;

    th->parse_in_eval = prev_parse_in_eval;
    th->base_block = prev_base_block;
}
