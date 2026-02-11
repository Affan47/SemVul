strreg(const void *ctx, const char *string, const char *regex, ...)
{
	size_t nmatch = 1 + strcount(regex, "(");
	regmatch_t *matches = talloc_array(ctx, regmatch_t, nmatch);
	regex_t r;
	bool ret;

	if (!matches || regcomp(&r, regex, REG_EXTENDED) != 0)
		return false;

	if (regexec(&r, string, nmatch, matches, 0) == 0) {
		unsigned int i;
		va_list ap;

		ret = true;
		va_start(ap, regex);
		for (i = 1; i < nmatch; i++) {
			char **arg;
			arg = va_arg(ap, char **);
			if (arg) {

				if (matches[i].rm_so == -1)
					*arg = NULL;
				else {
					*arg = talloc_strndup(ctx,
						      string + matches[i].rm_so,
						      matches[i].rm_eo
						      - matches[i].rm_so);
					if (!*arg) {
						ret = false;
						break;
					}
				}
			}
		}
		va_end(ap);
	} else
		ret = false;
	talloc_free(matches);
	regfree(&r);
	return ret;
}
