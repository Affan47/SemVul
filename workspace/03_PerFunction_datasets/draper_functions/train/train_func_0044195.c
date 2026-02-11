mod_tree_insert(struct module *mod)
{
	mod->core_layout.mtn.mod = mod;
	mod->init_layout.mtn.mod = mod;

	__mod_tree_insert(&mod->core_layout.mtn);
	if (mod->init_layout.size)
		__mod_tree_insert(&mod->init_layout.mtn);
}
