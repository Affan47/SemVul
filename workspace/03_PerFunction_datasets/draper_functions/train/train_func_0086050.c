srv_parse_verifyhost(char **args, int *cur_arg, struct proxy *px, struct server *newsrv, char **err)
{
	if (!*args[*cur_arg + 1]) {
		if (err)
			memprintf(err, "'%s' : missing hostname to verify against", args[*cur_arg]);
		return ERR_ALERT | ERR_FATAL;
	}

	newsrv->ssl_ctx.verify_host = strdup(args[*cur_arg + 1]);

	return 0;
}
