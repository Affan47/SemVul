tomoyo_update_manager_entry(const char *manager,
				       const bool is_delete)
{
	struct tomoyo_manager e = { };
	struct tomoyo_acl_param param = {

		.is_delete = is_delete,
		.list = &tomoyo_kernel_namespace.
		policy_list[TOMOYO_ID_MANAGER],
	};
	int error = is_delete ? -ENOENT : -ENOMEM;
	if (!tomoyo_correct_domain(manager) &&
	    !tomoyo_correct_word(manager))
		return -EINVAL;
	e.manager = tomoyo_get_name(manager);
	if (e.manager) {
		error = tomoyo_update_policy(&e.head, sizeof(e), &param,
					     tomoyo_same_manager);
		tomoyo_put_name(e.manager);
	}
	return error;
}
