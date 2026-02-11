cl_FF_p (const cl_number& x)
{
#if defined(CL_WIDE_POINTERS)
	if (!x.pointer_p())
		if (cl_tag((x).word) == cl_FF_tag)
			return true;
#else
	if (x.pointer_p())
		if (x.heappointer->type == &cl_class_ffloat)
			return true;
#endif
	return false;
}
