eb_narrow_font_character_bitmap(EB_Book *book, int character_number,
    char *bitmap)
{
    EB_Error_Code error_code;

    eb_lock(&book->lock);
    LOG(("in: eb_narrow_font_character_bitmap(book=%d, character_number=%d)",
	(int)book->code, character_number));


    if (book->subbook_current == NULL) {
	error_code = EB_ERR_NO_CUR_SUB;
	goto failed;
    }


    if (book->subbook_current->narrow_current == NULL) {
	error_code = EB_ERR_NO_CUR_FONT;
	goto failed;
    }

    if (book->character_code == EB_CHARCODE_ISO8859_1) {
	error_code = eb_narrow_character_bitmap_latin(book, character_number,
	    bitmap);
    } else {
	error_code = eb_narrow_character_bitmap_jis(book, character_number,
	    bitmap);
    }
    if (error_code != EB_SUCCESS)
	goto failed;

    LOG(("out: eb_narrow_font_character_bitmap() = %s",
	eb_error_string(EB_SUCCESS)));
    eb_unlock(&book->lock);

    return EB_SUCCESS;


  failed:
    *bitmap = '\0';
    LOG(("out: eb_narrow_font_character_bitmap() = %s",
	eb_error_string(error_code)));
    eb_unlock(&book->lock);
    return error_code;
}
