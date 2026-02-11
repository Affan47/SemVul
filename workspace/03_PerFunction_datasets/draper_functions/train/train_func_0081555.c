join_values_with_spaces(char *dst, char **src)
{
	if (dst != NULL) {
		*dst = '\0';
		if (src != NULL && *src != NULL) {
			strcat(dst, *src);

			for (src++; *src != NULL; src++) {
				strcat(dst, " ");
				strcat(dst, *src);
			}
		}
	}
	return(dst);
}
