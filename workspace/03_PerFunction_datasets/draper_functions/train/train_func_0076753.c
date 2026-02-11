stringlist_parsefunc(cp_value *v, const String &arg,
		     ErrorHandler *errh, const char *argname  CP_CONTEXT)
{
    const cp_argtype *argtype = v->argtype;
#ifndef CLICK_TOOL
    (void) context;
#endif

    if (HashTable<String, int> *m = reinterpret_cast<HashTable<String, int> *>(argtype->user_data)) {
	String word;
	if (cp_word(arg, &word))
	    if (HashTable<String, int>::iterator it = m->find(word)) {
		v->v.s32 = it.value();
		return;
	    }
    }

    if (argtype->flags & cpArgAllowNumbers) {
	if (!cp_integer(arg, &v->v.s32))
	    errh->error("%s has type %s", argname, argtype->description);
	else if (cp_errno == CPE_OVERFLOW)
	    errh->error("%s out of range, bound %d", argname, v->v.s32);
    } else
	errh->error("%s has type %s", argname, argtype->description);
}
