command_flag_stringarray_get (command_context_t *ctx, const gchar *name, const gchar ***v)
{
	command_argument_t *arg;
	gboolean retval = FALSE;

	arg = (command_argument_t *) g_hash_table_lookup (ctx->flags, name);
	if (arg && arg->type == COMMAND_ARGUMENT_TYPE_STRING_ARRAY && arg->value.vstringv) {
		*v = (const gchar **) arg->value.vstringv;
		retval = TRUE;
	}

	return retval;
}
