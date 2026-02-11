validate_var_name(const char *s, void *ctx)
{
	struct var *var = ctx;

	if (!is_id(s))
		return 0;
	if (var->key)
		return 1;
	return !find_var_in_frame(var->frame, s, var);
}
