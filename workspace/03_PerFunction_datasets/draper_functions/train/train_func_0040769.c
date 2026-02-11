klp_module_notify_going(struct klp_patch *patch,
				    struct klp_object *obj)
{
	struct module *pmod = patch->mod;
	struct module *mod = obj->mod;

	if (patch->state == KLP_DISABLED)
		goto disabled;

	pr_notice("reverting patch '%s' on unloading module '%s'\n",
		  pmod->name, mod->name);

	klp_disable_object(obj);

disabled:
	klp_free_object_loaded(obj);
}
