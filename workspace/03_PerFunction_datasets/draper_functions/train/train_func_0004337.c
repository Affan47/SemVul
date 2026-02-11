base64encode(const wxString& str)
{


	static const char *base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	wxString buf;

	const wxWX2MBbuf utf8 = str.mb_str(wxConvUTF8);
	const char* from = utf8;

	size_t len = strlen(from);
	while (len >= 3) {
		buf << wxString::Format(wxT("%c%c"), base64[(from[0] >> 2) & 0x3f], base64[((from[0] << 4) & 0x30) | ((from[1] >> 4) & 0xf)]);
		buf << wxString::Format(wxT("%c%c"), base64[((from[1] << 2) & 0x3c) | ((from[2] >> 6) & 0x3)], base64[from[2] & 0x3f]);
		from += 3;
		len -= 3;
	}
	if (len > 0) {
		buf << wxString::Format(wxT("%c"), base64[(from[0] >> 2) & 0x3f]);
		if (len == 1) {
			buf << wxString::Format(wxT("%c="), base64[(from[0] << 4) & 0x30]);
		} else {
			buf << wxString::Format(wxT("%c%c"), base64[((from[0] << 4) & 0x30) | ((from[1] >> 4) & 0xf)], base64[(from[1] << 2) & 0x3c]);
		}
		buf << wxString::Format(wxT("="));
	}

	return buf;
}
