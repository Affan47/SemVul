eb_set_font(EB_Book *book, EB_Font_Code font_code)
{
    EB_Error_Code error_code;
    EB_Subbook *subbook;

    eb_lock(&book->lock);
    LOG(("in: eb_set_font(book=%d, font_code=%d)", (int)book->code,
	(int)font_code));


    if (font_code < 0 || EB_MAX_FONTS <= font_code) {
	error_code = EB_ERR_NO_SUCH_FONT;
	goto failed;
    }


    subbook = book->subbook_current;
    if (subbook == NULL) {
	error_code = EB_ERR_NO_CUR_SUB;
	goto failed;
    }


    if (subbook->narrow_current != NULL) {
	if (subbook->narrow_current->font_code == font_code)
	    goto succeeded;
	if (book->disc_code == EB_DISC_EPWING)
	    zio_close(&subbook->narrow_current->zio);
	subbook->narrow_current = NULL;
    }
    if (subbook->wide_current != NULL) {
	if (subbook->wide_current->font_code == font_code)
	    goto succeeded;
	if (book->disc_code == EB_DISC_EPWING)
	    zio_close(&subbook->wide_current->zio);
	subbook->wide_current = NULL;
    }


    if (subbook->narrow_fonts[font_code].font_code != EB_FONT_INVALID)
	subbook->narrow_current = subbook->narrow_fonts + font_code;
    if (subbook->wide_fonts[font_code].font_code != EB_FONT_INVALID)
	subbook->wide_current = subbook->wide_fonts + font_code;

    if (subbook->narrow_current == NULL && subbook->wide_current == NULL) {
	error_code = EB_ERR_NO_SUCH_FONT;
	goto failed;
    }


    if (subbook->narrow_current != NULL) {
	error_code = eb_open_narrow_font_file(book, font_code);
	if (error_code != EB_SUCCESS)
	    goto failed;
	if (is_ebnet_url(book->path)) {
	    error_code = eb_load_narrow_font_glyphs(book, font_code);
	    if (error_code != EB_SUCCESS)
		goto failed;
	}
    }
    if (subbook->wide_current != NULL) {
	error_code = eb_open_wide_font_file(book, font_code);
	if (error_code != EB_SUCCESS)
	    goto failed;
	if (is_ebnet_url(book->path)) {
	    error_code = eb_load_wide_font_glyphs(book, font_code);
	    if (error_code != EB_SUCCESS)
		goto failed;
	}
    }


  succeeded:
    LOG(("out: eb_set_font() = %s", eb_error_string(EB_SUCCESS)));
    eb_unlock(&book->lock);

    return EB_SUCCESS;


  failed:
    eb_unset_font(book);
    LOG(("out: eb_set_font() = %s", eb_error_string(error_code)));
    return error_code;
}
