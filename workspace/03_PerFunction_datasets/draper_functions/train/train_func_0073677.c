GetModifiers(FormatList::const_iterator it) const
{
	wxString result = wxT("%");
	if (it->flag != wxT('\0')) {
		result += it->flag;
	}
	if (it->width > 0) {
		result += wxString::Format(wxT("%u"), it->width);
	}
	if (it->precision >= 0) {
		result += wxString::Format(wxT(".%u"), it->precision);
	}
	return result;
}
