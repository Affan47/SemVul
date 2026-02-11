rb_mod_to_s(klass)
    VALUE klass;

{
    if (FL_TEST(klass, FL_SINGLETON)) {
	VALUE s = rb_str_new2("#<");
	VALUE v = rb_iv_get(klass, "__attached__");

	rb_str_cat2(s, "Class:");
	switch (TYPE(v)) {
	  case T_CLASS: case T_MODULE:
	    rb_str_append(s, rb_inspect(v));
	    break;
	  default:
	    rb_str_append(s, rb_any_to_s(v));
	    break;
	}
	rb_str_cat2(s, ">");

	return s;
    }
    return rb_str_dup(rb_class_name(klass));
}
