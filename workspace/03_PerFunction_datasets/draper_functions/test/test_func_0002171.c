rb_class_superclass(VALUE klass)
{
    VALUE super = RCLASS_SUPER(klass);

    if (!super) {
	if (klass == rb_cBasicObject) return Qnil;
	rb_raise(rb_eTypeError, "uninitialized class");
    }
    while (TYPE(super) == T_ICLASS) {
	super = RCLASS_SUPER(super);
    }
    if (!super) {
	return Qnil;
    }
    return super;
}
