enumerator_init_copy(VALUE obj, VALUE orig)
{
    struct enumerator *ptr0, *ptr1;

    ptr0 = enumerator_ptr(orig);
    if (ptr0->fib) {

	rb_raise(rb_eTypeError, "can't copy execution context");
    }

    TypedData_Get_Struct(obj, struct enumerator, &enumerator_data_type, ptr1);

    if (!ptr1) {
	rb_raise(rb_eArgError, "unallocated enumerator");
    }

    ptr1->obj  = ptr0->obj;
    ptr1->meth = ptr0->meth;
    ptr1->args = ptr0->args;
    ptr1->fib  = 0;
    ptr1->lookahead  = Qundef;
    ptr1->feedvalue  = Qundef;

    return obj;
}
