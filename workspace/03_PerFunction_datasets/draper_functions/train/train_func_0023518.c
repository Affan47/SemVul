toString(string& str) const {
	if (m_fname == "") {
		str = m_txt;
	} else {
		ostringstream err_str;
		write(err_str);
		str = err_str.str();
	}
}
