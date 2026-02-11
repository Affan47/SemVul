doAccent(docstring const & s, tex_accent accent)
{
	if (s.empty())
		return docstring(1, lyx_accent_table[accent].ucs4);

	odocstringstream os;
	os.put(s[0]);
	os.put(lyx_accent_table[accent].ucs4);
	if (s.length() > 1) {
		if (accent != TEX_TIE || s.length() > 2)
			lyxerr << "Warning: Too many characters given for accent "
			       << lyx_accent_table[accent].name << '.' << endl;
		os << s.substr(1);
	}
	return normalize_c(os.str());
}
