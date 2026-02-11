check_before_mod_set(VALUE klass, ID id, VALUE val, const char *dest)
{
    if (!OBJ_UNTRUSTED(klass) && rb_safe_level() >= 4)
	rb_raise(rb_eSecurityError, "Insecure: can't set %s", dest);
    rb_check_frozen(klass);
}
