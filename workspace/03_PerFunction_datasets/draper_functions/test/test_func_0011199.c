addDeadkey(tex_accent accent, docstring const & keys)
{
	KmodInfo tmp;
	tmp.data = keys;
	tmp.accent = accent;
	kmod_list_[accent] = tmp;

	for (docstring::size_type i = 0; i < keys.length(); ++i) {


		docstring tmp;
		tmp += char_type(0);
		tmp += char_type(accent);
		keymap_[keys[i]] = tmp;
	}
}
