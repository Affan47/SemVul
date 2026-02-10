parse_byte_size(const std::string& str, uint64_t& bytes, bool extended)
{


	std::vector<std::string> to_replace;
	to_replace.push_back(" ");
	to_replace.push_back("'");
	to_replace.push_back(",");
	to_replace.push_back(".");
	to_replace.push_back(std::string(1, 0xa0));

#ifdef _WIN32


	{
		std::string old_locale = hz::locale_c_get();
		hz::ScopedCLocale loc("", old_locale == "C");

		struct lconv* lc = std::localeconv();
		if (lc && lc->thousands_sep && *(lc->thousands_sep)) {
			to_replace.push_back(lc->thousands_sep);
		}
	}
#endif

	to_replace.push_back("bytes");
	std::string s = hz::string_replace_array_copy(hz::string_trim_copy(str), to_replace, "");

	uint64_t v = 0;
	if (hz::string_is_numeric(s, v, false)) {
		bytes = v;
		return hz::format_size(v, true) + (extended ?
				" [" + hz::format_size(v, false) + ", " + hz::number_to_string(v) + " bytes]" : "");
	}

	return std::string();
}
