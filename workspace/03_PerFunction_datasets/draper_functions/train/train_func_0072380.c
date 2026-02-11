cl_RA_p (const cl_number& x)
{
	return (!x.pointer_p()
		? x.nonpointer_tag() == cl_FN_tag
		: (x.pointer_type()->flags & cl_class_flags_subclass_rational) != 0);
}
