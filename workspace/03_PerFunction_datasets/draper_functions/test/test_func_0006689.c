listexternal(void *arg, char *key, void *value) {
	if ((((Var *) value)->flags & var_isinternal) == 0 && !specialvar(key))
		addtolist(arg, key, value);
}
