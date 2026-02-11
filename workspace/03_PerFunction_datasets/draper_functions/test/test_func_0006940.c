rb_class_inherited_p(VALUE mod, VALUE arg)
{
    VALUE start = mod;

    if (mod == arg) return Qtrue;
    switch (TYPE(arg)) {
      case T_MODULE:
      case T_CLASS:
	break;
      default:
	rb_raise(rb_eTypeError, "compared with non class/module");
    }
    while (mod) {
	if (RCLASS_M_TBL(mod) == RCLASS_M_TBL(arg))
	    return Qtrue;
	mod = RCLASS_SUPER(mod);
    }

    while (arg) {
	if (RCLASS_M_TBL(arg) == RCLASS_M_TBL(start))
	    return Qfalse;
	arg = RCLASS_SUPER(arg);
    }
    return Qnil;
}
