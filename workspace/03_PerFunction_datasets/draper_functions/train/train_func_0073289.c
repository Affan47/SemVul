set_popdown_strings (Gtk::ComboBoxText& cr, const vector<string>& strings, bool set_size, gint hpadding, gint vpadding)
{
	vector<string>::const_iterator i;

	cr.clear ();

	if (set_size) {
		vector<string> copy;

		for (i = strings.begin(); i != strings.end(); ++i) {
			if ((*i).find_first_of ("gy") != string::npos) {

				break;
			}
		}

		if (i == strings.end()) {


			copy = strings;
			copy.push_back ("g");
			set_size_request_to_display_given_text (cr, copy, COMBO_FUDGE+10+hpadding, 15+vpadding);

		} else {
			set_size_request_to_display_given_text (cr, strings, COMBO_FUDGE+10+hpadding, 15+vpadding);
		}
	}

	for (i = strings.begin(); i != strings.end(); ++i) {
		cr.append_text (*i);
	}
}
