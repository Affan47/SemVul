getkeymod(string const & p)

{
	for (int i = 1; i <= TEX_MAX_ACCENT; ++i) {
		LYXERR(Debug::KBMAP, "p = " << p
		       << ", lyx_accent_table[" << i
		       << "].name = `" << lyx_accent_table[i].name << '\'');

		if (lyx_accent_table[i].name
		     && contains(p, lyx_accent_table[i].name)) {
			LYXERR(Debug::KBMAP, "Found it!");
			return static_cast<tex_accent>(i);
		}
	}
	return TEX_NOACCENT;
}
