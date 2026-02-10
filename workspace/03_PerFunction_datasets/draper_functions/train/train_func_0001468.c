jabber_params_split(const char *line, int allow_empty)
{
	char **arr, **ret = NULL;
	int num = 0, i = 0, z = 0;

	if (!line)
		return NULL;

	arr = array_make(line, " ", 0, 1, 1);
	while (arr[i]) {
		ret = (char **)xrealloc (ret, (num + 2)*sizeof (char *));

		if (!z) {
			if (arr[i][0] == '-' && arr[i][1] == '-' && xstrlen(arr[i]) > 2)
				ret[num++] = xstrdup (arr[i]+2);
			else if (allow_empty) {
				ret[num++] = xstrdup("");
			} else {
				array_free (arr);
				ret[num] = NULL;
				array_free (ret);
				return NULL;

			}
			i++;
		} else {


			if (arr[i][0] == '-' && arr[i][1] == '-' && xstrlen(arr[i]) > 2)
				ret[num++] = xstrdup("");
			else {
				ret[num++] = xstrdup(arr[i]);
				i++;
			}
		}
		z^=1;
	}

	if (z) {
		ret = (char **)xrealloc (ret, (num + 2)*sizeof (char *));
		ret[num++] = xstrdup("");
	}
	ret [num] = NULL;

	array_free (arr);
	i = 0;
	while (ret[i]) {
		debug (" *[%d]* %s\n", i, ret[i]);
		i++;
	}
	return ret;
}
