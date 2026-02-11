tomoyo_write_env(struct tomoyo_acl_param *param)
{
	struct tomoyo_env_acl e = { .head.type = TOMOYO_TYPE_ENV_ACL };
	int error = -ENOMEM;
	const char *data = tomoyo_read_token(param);

	if (!tomoyo_correct_word(data) || strchr(data, '='))
		return -EINVAL;
	e.env = tomoyo_get_name(data);
	if (!e.env)
		return error;
	error = tomoyo_update_domain(&e.head, sizeof(e), param,
				  tomoyo_same_env_acl, NULL);
	tomoyo_put_name(e.env);
	return error;
}
