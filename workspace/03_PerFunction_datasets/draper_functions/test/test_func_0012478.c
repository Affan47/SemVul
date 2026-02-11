converted(const char *str,
						size_t n)
{
	const unicode_char *uc=reinterpret_cast<const unicode_char *>(str);
	n /= sizeof(unicode_char);

	while (n)
	{
		mail::Search::operator<<(*uc);
		++uc;
		--n;
	}
	return 0;
}
