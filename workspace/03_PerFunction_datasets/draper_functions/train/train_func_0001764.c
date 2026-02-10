rb_class_path(VALUE klass)
{
    VALUE path = classname(klass);
    st_data_t n = (st_data_t)path;

    if (!NIL_P(path)) return path;
    if (RCLASS_IV_TBL(klass) && st_lookup(RCLASS_IV_TBL(klass),
					  (st_data_t)tmp_classpath, &n)) {
	return (VALUE)n;
    }
    else {
	const char *s = "Class";

	if (TYPE(klass) == T_MODULE) {
	    if (rb_obj_class(klass) == rb_cModule) {
		s = "Module";
	    }
	    else {
		s = rb_class2name(RBASIC(klass)->klass);
	    }
	}
	path = rb_sprintf("#<%s:%p>", s, (void*)klass);
	OBJ_FREEZE(path);
	rb_ivar_set(klass, tmp_classpath, path);

	return path;
    }
}
