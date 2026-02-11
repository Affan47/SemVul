element_error_hook(int, VA_LIST_REF_T val)
{
    const Element *e = va_arg(VA_LIST_DEREF(val), const Element *);
    if (e)
	return e->declaration();
    else
	return String::make_stable("(null)", 6);
}
