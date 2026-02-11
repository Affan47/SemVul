lookup_clipboard()
{
	static Glib::ustring last_clp_word;
	Glib::ustring tmp(""), buf("");

	if (clp->wait_is_text_available()) {
		tmp = clp->wait_for_text();

		if (!tmp.length()) {
			return true;
		}


		Glib::ustring::iterator it = tmp.begin();
		for (int i = 0; (it != tmp.end()) && (i < 20); it++, i++) {

			if (Glib::Unicode::isalpha(*it)) {
				buf += *it;
			} else {
				return true;
			}
		}


		if (buf != last_clp_word) {
			entry.set_text(buf);
			last_clp_word = buf;

#ifndef ENABLE_LIGHT_VERSION
			helper.show_help();
#endif
		}
	}


	return true;
}
