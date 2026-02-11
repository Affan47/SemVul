rb_obj_singleton_methods(int argc, VALUE *argv, VALUE obj)
{
    VALUE recur, ary, klass;
    st_table *list;

    if (argc == 0) {
	recur = Qtrue;
    }
    else {
	rb_scan_args(argc, argv, "01", &recur);
    }
    klass = CLASS_OF(obj);
    list = st_init_numtable();
    if (klass && FL_TEST(klass, FL_SINGLETON)) {
	st_foreach(RCLASS_M_TBL(klass), method_entry_i, (st_data_t)list);
	klass = RCLASS_SUPER(klass);
    }
    if (RTEST(recur)) {
	while (klass && (FL_TEST(klass, FL_SINGLETON) || TYPE(klass) == T_ICLASS)) {
	    st_foreach(RCLASS_M_TBL(klass), method_entry_i, (st_data_t)list);
	    klass = RCLASS_SUPER(klass);
	}
    }
    ary = rb_ary_new();
    st_foreach(list, ins_methods_i, ary);
    st_free_table(list);

    return ary;
}
