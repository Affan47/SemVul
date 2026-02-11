do_subst(const char *s, Boolean do_vars, Boolean do_tilde)
{
	if (!do_vars && !do_tilde)
		return NewString(s);

	if (do_vars) {
		char *t;

		t = var_subst(s);
#if !defined(_WIN32)
		if (do_tilde) {
			char *u;

			u = tilde_subst(t);
			Free(t);
			return u;
		}
#endif
		return t;
	}

#if !defined(_WIN32)
	return tilde_subst(s);
#else
	return NewString(s);
#endif
}
