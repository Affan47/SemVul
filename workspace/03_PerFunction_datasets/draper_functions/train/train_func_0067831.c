get_string_truncated(size_t maxwidth, ssize_t col) const
{
	std::pair<std::vector<unicode_char>, size_t>
		tempret(get_unicode_truncated(maxwidth, col));

	std::pair<std::string, size_t> ret;

	ret.second=tempret.second;

	mail::iconvert::fromu::convert(tempret.first, unicode_default_chset(),
				       ret.first);
	return ret;
}
