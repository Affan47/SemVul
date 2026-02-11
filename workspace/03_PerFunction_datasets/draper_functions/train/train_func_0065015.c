rb_struct_initialize_m(int argc, VALUE *argv, VALUE self)
{
    VALUE klass = rb_obj_class(self);
    long n;

    rb_struct_modify(self);
    n = num_members(klass);
    if (n < argc) {
	rb_raise(rb_eArgError, "struct size differs");
    }
    MEMCPY(RSTRUCT_PTR(self), argv, VALUE, argc);
    if (n > argc) {
	rb_mem_clear(RSTRUCT_PTR(self)+argc, n-argc);
    }
    return Qnil;
}
