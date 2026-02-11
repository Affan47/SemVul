rb_cvar_set(VALUE klass, ID id, VALUE val)
{
    VALUE tmp, front = 0, target = 0;

    tmp = klass;
    CVAR_LOOKUP(0, {if (!front) front = klass; target = klass;});
    if (target) {
	if (front && target != front) {
	    st_data_t did = id;

	    if (RTEST(ruby_verbose)) {
		rb_warning("class variable %s of %s is overtaken by %s",
			   rb_id2name(id), rb_class2name(original_module(front)),
			   rb_class2name(original_module(target)));
	    }
	    if (BUILTIN_TYPE(front) == T_CLASS) {
		st_delete(RCLASS_IV_TBL(front),&did,0);
	    }
	}
    }
    else {
	target = tmp;
    }

    check_before_mod_set(target, id, val, "class variable");
    if (!RCLASS_IV_TBL(target)) {
	RCLASS_IV_TBL(target) = st_init_numtable();
    }

    st_insert(RCLASS_IV_TBL(target), (st_data_t)id, (st_data_t)val);
}
