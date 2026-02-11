gravity_parse_multi_dir_argument(
	char *action, char **ret_action)
{
	int rc = MULTI_DIR_NONE;
	char *token, *str;
	direction_t dir = gravity_parse_dir_argument(action, ret_action, -1);

	if (dir != -1)
	{
		rc = (1 << dir);
	}
	else
	{
		token = PeekToken(action, &str);
		if (StrEquals(token, "all"))
		{
			rc = MULTI_DIR_ALL;
			*ret_action = str;
		}
		else
		{
			rc = MULTI_DIR_NONE;
		}
	}

	return (multi_direction_t)rc;
}
