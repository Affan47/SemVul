blank_text(vxml_parser_t *vp,
	unsigned id, const char *text, size_t len, void *data)
{
	struct vxml_test_info *info = data;
	const char *unstripped = "   <x> <y>  &unknown; </x> [[/]] data      ";
	const char *stripped = "<x> <y>  &unknown; </x> [[/]] data";
	bool stripping = GPOINTER_TO_UINT(info->data);

	if (vxml_debugging(0)) {
		g_info("VXML test #%d \"%s\": "
			"blank_text: got \"%s\" (%zu byte%s) in <token #%u> at depth %u",
			info->num, info->name, text, len, 1 == len ? "" : "s",
			id, vxml_parser_depth(vp));
	}

	g_assert(T_TEST == id);
	g_assert(0 == strcmp(text, stripping ? stripped : unstripped));
}
