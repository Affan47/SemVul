vardef(char *name, Binding *binding, List *defn) {
	Var *var;

	validatevar(name);
	for (; binding != NULL; binding = binding->next)
		if (streq(name, binding->name)) {
			binding->defn = defn;
			rebound = TRUE;
			return;
		}

	RefAdd(name);
	defn = callsettor(name, defn);
	if (isexported(name))
		isdirty = TRUE;

	var = dictget(vars, name);
	if (var != NULL)
		if (defn != NULL) {
			var->defn = defn;
			var->env = NULL;
			var->flags = hasbindings(defn) ? var_hasbindings : 0;
		} else
			vars = dictput(vars, name, NULL);
	else if (defn != NULL) {
		var = mkvar(defn);
		vars = dictput(vars, name, var);
	}
	RefRemove(name);
}
