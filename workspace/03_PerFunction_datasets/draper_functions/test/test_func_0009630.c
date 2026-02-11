set_text (const ustring& text, bool use_markup, bool use_underline)
{
	if (use_markup) {
		if (use_underline)
			label.set_markup_with_mnemonic (text);
		else
			label.set_markup (text);
	} else {
		if (use_underline)
			label.set_text_with_mnemonic (text);
		else
			label.set_text (text);
	}
}
