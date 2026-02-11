klp_init_object_loaded(struct klp_patch *patch,
				  struct klp_object *obj)
{
	struct klp_func *func;
	int ret;

	if (obj->relocs) {
		ret = klp_write_object_relocations(patch->mod, obj);
		if (ret)
			return ret;
	}

	klp_for_each_func(obj, func) {
		ret = klp_find_object_symbol(obj->name, func->old_name,
					     func->old_sympos,
					     &func->old_addr);
		if (ret)
			return ret;
	}

	return 0;
}
