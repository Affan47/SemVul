unicode_convert_fromchset(const char *txt, const char *from,
		      const struct unicode_info *to)
{
	const struct unicode_info *fromu=unicode_find(from);

	if (!fromu)
	{
		errno=EINVAL;
		return (0);
	}
	return (unicode_convert(txt, fromu, to));
}
