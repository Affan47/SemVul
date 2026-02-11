cp_extend_stringlist_argtype(const char *name, ...)
{
    cp_argtype *t = const_cast<cp_argtype *>(cp_find_argtype(name));
    if (!t || t->parse != stringlist_parsefunc)
	return -ENOENT;
    HashMap<String, int> *m = reinterpret_cast<HashMap<String, int> *>(t->user_data);
    if (!m)
	t->user_data = m = new HashMap<String, int>();
    if (!m)
	return -ENOMEM;

    va_list val;
    va_start(val, name);
    const char *s;
    int retval = 0;
    while ((s = va_arg(val, const char *))) {
	int value = va_arg(val, int);
	if (cp_is_word(s))
	    m->insert(String(s), value);
	else
	    retval = -1;
    }
    va_end(val);
    return retval;
}
