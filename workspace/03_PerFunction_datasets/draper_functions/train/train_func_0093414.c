hook_reference(EB_Book *book, EB_Appendix *appendix, void *container, EB_Hook_Code code, int argc, const unsigned int *argv)
{
	gchar text[64];


	switch (code) {
	case EB_HOOK_BEGIN_REFERENCE:
		sprintf (text, "<reference>");
		eb_write_text_string(book, text);
		break;
	case EB_HOOK_END_REFERENCE:
		sprintf (text, "</reference page=0x%x offset=0x%x>", argv[1], argv[2]);
		eb_write_text_string(book, text);
		break;
	}
	return EB_SUCCESS;

}
