fmt_error(char *s)
{
	vs_push(make_simple_string(s));
	vs_push(make_fixnum(&ctl_string[ctl_index] - fmt_string->st.st_self));
	FEerror("Format error: ~A.~%~V@TV~%\"~A\"~%",
		3, vs_top[-2], vs_top[-1], fmt_string);
}
