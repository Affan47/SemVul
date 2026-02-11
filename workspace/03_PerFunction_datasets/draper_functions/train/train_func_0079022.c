_assert_VSB_integrity(const char *fun, struct vsb *s)
{

	(void)fun;
	(void)s;
	KASSERT(s != NULL,
	    ("%s called with a NULL vsb pointer", fun));
	KASSERT(s->s_magic == VSB_MAGIC,
	    ("%s called wih an unintialized vsb pointer", fun));
	KASSERT(s->s_buf != NULL,
	    ("%s called with uninitialized or corrupt vsb", fun));
	KASSERT(s->s_len < s->s_size,
	    ("wrote past end of vsb (%d >= %d)", s->s_len, s->s_size));
}
