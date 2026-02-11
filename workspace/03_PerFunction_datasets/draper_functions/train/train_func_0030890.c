quitmsg_is_split(const char *msg)
{
	const char *host2, *p;
        int prev, len, host1_dot, host2_dot;

	g_return_val_if_fail(msg != NULL, FALSE);


	host2 = NULL;
	prev = '\0'; len = 0; host1_dot = host2_dot = 0;
	while (*msg != '\0') {
		if (*msg == ' ') {
			if (prev == '.' || prev == '\0') {


				return FALSE;
			}
			if (host2 != NULL)
				return FALSE;
			if (!host1_dot)
                                return FALSE;
                        host2 = msg+1; len = -1;
		} else if (*msg == '.') {
			if (prev == '\0' || prev == ' ' || prev == '.') {


				return FALSE;
			}

			if (host2 != NULL)
				host2_dot = TRUE;
			else
                                host1_dot = TRUE;
		} else if (*msg == ':' || *msg == '/')
			return FALSE;

		prev = *msg;
                msg++; len++;
	}

	if (!host2_dot || prev == '.')
                return FALSE;


	p = host2-1;
	while (p[-1] != '.') {
		if (!i_isalpha(p[-1]))
                        return FALSE;
		p--;
	}
	if (host2-p-1 < 2) return FALSE;


	p = host2+strlen(host2);
	while (p[-1] != '.') {
		if (!i_isalpha(p[-1]))
                        return FALSE;
		p--;
	}
	if (strlen(p) < 2) return FALSE;

        return TRUE;
}
