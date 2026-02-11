map_set_editor(EditLine *el, Char *editor)
{

	if (Strcmp(editor, STR("emacs")) == 0) {
		map_init_emacs(el);
		return 0;
	}
	if (Strcmp(editor, STR("vi")) == 0) {
		map_init_vi(el);
		return 0;
	}
	return -1;
}
