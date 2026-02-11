w_class(char type, VALUE obj, struct dump_arg *arg, int check)
{
    VALUE path;
    st_data_t real_obj;
    VALUE klass;

    if (st_lookup(arg->compat_tbl, (st_data_t)obj, &real_obj)) {
        obj = (VALUE)real_obj;
    }
    klass = CLASS_OF(obj);
    w_extended(klass, arg, check);
    w_byte(type, arg);
    path = class2path(rb_class_real(klass));
    w_unique(path, arg);
}
