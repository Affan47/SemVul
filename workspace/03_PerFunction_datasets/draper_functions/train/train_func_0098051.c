fixup_line(const char *ptr, int quote_count)
{
	char *str = git__malloc(strlen(ptr) + 1);
	char *out = str, *esc;
	const char *escapes = "ntb\"\\";
	const char *escaped = "\n\t\b\"\\";

	if (str == NULL)
		return NULL;

	while (*ptr != '\0') {
		if (*ptr == '"') {
			quote_count++;
		} else if (*ptr != '\\') {
			*out++ = *ptr;
		} else {

			ptr++;

			if (*ptr == '\0') {
				*out++ = '\\';
				goto out;
			}
			if ((esc = strchr(escapes, *ptr)) != NULL) {
				*out++ = escaped[esc - escapes];
			} else {
				git__free(str);
				giterr_set(GITERR_CONFIG, "Invalid escape at %s", ptr);
				return NULL;
			}
		}
		ptr++;
	}

out:
	*out = '\0';

	return str;
}
