SetTextFormat(const char* text, ...) {
	va_list ap;
	va_start(ap, text);
	char temp[256];

	if(text == NULL) {
		my_text = "";
		return;
	}

	if(text[0] == 0) {
		my_text = "";
		return;
	}

	vsprintf(temp, text, ap);
	SetText(temp);
	va_end(ap);
}
