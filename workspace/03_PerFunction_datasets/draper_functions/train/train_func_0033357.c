hook_narrow_font_text(book, appendix, container, code, argc, argv)
    EB_Book *book;
    EB_Appendix *appendix;
    void *container;
    EB_Hook_Code code;
    int argc;
    const unsigned int *argv;
{
    char alt_text[EB_MAX_ALTERNATION_TEXT_LENGTH + 1];

    if (eb_narrow_alt_character_text(appendix, argv[0], alt_text)
	!= EB_SUCCESS)
	sprintf(alt_text, "#%04x", argv[0]);
    eb_write_text_string(book, alt_text);

    return EB_SUCCESS;
}
