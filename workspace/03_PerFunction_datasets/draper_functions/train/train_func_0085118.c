parse_vorbis_comment_field_name(const char *field_ref, char **name, const char **violation)
{
	static const char * const violations[] = {
		"field name contains invalid character"
	};

	char *q, *s;

	s = local_strdup(field_ref);

	for(q = s; *q; q++) {
		if(*q < 0x20 || *q > 0x7d || *q == 0x3d) {
			free(s);
			*violation = violations[0];
			return false;
		}
	}

	*name = s;

	return true;
}
