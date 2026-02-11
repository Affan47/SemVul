mod_add_dependency(struct mod *mod, struct symbol *sym)
{
	int err;

	DBG("%s depends on %s %s\n", mod->path, sym->name,
	    sym->owner != NULL ? sym->owner->path : "(unknown)");

	if (sym->owner == NULL)
		return 0;

	err = array_append_unique(&mod->deps, sym->owner);
	if (err == -EEXIST)
		return 0;
	if (err < 0)
		return err;

	sym->owner->users++;
	SHOW("%s needs \"%s\": %s\n", mod->path, sym->name, sym->owner->path);
	return 0;
}
