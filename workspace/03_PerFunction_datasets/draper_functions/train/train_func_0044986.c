rb_dlcfunc_set_ptr(VALUE self, VALUE addr)
{
    struct cfunc_data *cfunc;

    TypedData_Get_Struct(self, struct cfunc_data, &dlcfunc_data_type, cfunc);
    cfunc->ptr = NUM2PTR(addr);

    return Qnil;
}
