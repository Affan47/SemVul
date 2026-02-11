rb_str_unlocktmp(str)
    VALUE str;
{
    if (!FL_TEST(str, STR_TMPLOCK)) {
	rb_raise(rb_eRuntimeError, "temporal unlocking already unlocked string");
    }
    FL_UNSET(str, STR_TMPLOCK);
    return str;
}
