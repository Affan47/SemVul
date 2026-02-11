version_cmp(const char *v1, const char *v2)
{
	int x[2][4] = { {0, 0, 0, 0}, {0, 0, 0, 0} };
	const char *v[2] = { v1, v2 };
	const char *tmp, *tmp2;

	int i, j;

	for (i = 0; i < 2; i++) {
		tmp = v[i];
		for (j = 0; j < 4; j++) {
			if (!strncmp(tmp, "pre", strlen("pre")))
				x[i][j] = 0 - atoi(tmp + strlen("pre"));
			else
				x[i][j] = atoi(tmp);

			tmp2 = tmp;
			tmp = strchr(tmp, '.');
			if (tmp)
				tmp++;
			else {
				tmp = strchr(tmp2, '-');
				if (tmp)
					tmp++;
				else
					break;
			}
		}
	}

	for (j = 0; j < 4; j++)
		if (x[0][j] != x[1][j])
			return x[0][j] - x[1][j];

	return 0;
}
