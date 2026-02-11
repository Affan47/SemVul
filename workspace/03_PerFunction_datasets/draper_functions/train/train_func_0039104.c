rb_dlptr_eql(VALUE self, VALUE other)
{
    void *ptr1, *ptr2;

    if(!rb_obj_is_kind_of(other, rb_cDLCPtr)) return Qfalse;

    ptr1 = rb_dlptr2cptr(self);
    ptr2 = rb_dlptr2cptr(other);

    return ptr1 == ptr2 ? Qtrue : Qfalse;
}
