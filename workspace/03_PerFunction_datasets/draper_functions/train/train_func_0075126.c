local_devicestate(const char *data)
{
	char *exten = ast_strdupa(data);
	char *context = NULL, *opts = NULL;
	int res;
	struct local_pvt *lp;
	struct ao2_iterator it;

	if (!(context = strchr(exten, '@'))) {
		ast_log(LOG_WARNING, "Someone used Local/%s somewhere without a @context. This is bad.\n", exten);
		return AST_DEVICE_INVALID;
	}

	*context++ = '\0';


	if ((opts = strchr(context, '/')))
		*opts = '\0';

	ast_debug(3, "Checking if extension %s@%s exists (devicestate)\n", exten, context);

	res = ast_exists_extension(NULL, context, exten, 1, NULL);
	if (!res)
		return AST_DEVICE_INVALID;

	res = AST_DEVICE_NOT_INUSE;

	it = ao2_iterator_init(locals, 0);
	for (; (lp = ao2_iterator_next(&it)); ao2_ref(lp, -1)) {
		int is_inuse;

		ao2_lock(lp);
		is_inuse = !strcmp(exten, lp->exten)
			&& !strcmp(context, lp->context)
			&& lp->owner
			&& ast_test_flag(lp, LOCAL_LAUNCHED_PBX);
		ao2_unlock(lp);
		if (is_inuse) {
			res = AST_DEVICE_INUSE;
			ao2_ref(lp, -1);
			break;
		}
	}
	ao2_iterator_destroy(&it);

	return res;
}
