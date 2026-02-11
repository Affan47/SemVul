klp_enable_object(struct klp_object *obj)
{
	struct klp_func *func;
	int ret;

	if (WARN_ON(obj->state != KLP_DISABLED))
		return -EINVAL;

	if (WARN_ON(!klp_is_object_loaded(obj)))
		return -EINVAL;

	klp_for_each_func(obj, func) {
		ret = klp_enable_func(func);
		if (ret) {
			klp_disable_object(obj);
			return ret;
		}
	}
	obj->state = KLP_ENABLED;

	return 0;
}
