eb_tell_text(EB_Book *book, EB_Position *position)
{
    EB_Error_Code error_code;

    eb_lock(&book->lock);
    LOG(("in: eb_tell_text(book=%d)", (int)book->code));


    if (book->subbook_current == NULL) {
	error_code = EB_ERR_NO_CUR_SUB;
	goto failed;
    }
    if (zio_file(&book->subbook_current->text_zio) < 0) {
	error_code = EB_ERR_NO_TEXT;
	goto failed;
    }

    position->page = book->text_context.location / EB_SIZE_PAGE + 1;
    position->offset = book->text_context.location % EB_SIZE_PAGE;

    LOG(("out: eb_seek_text(position={%d,%d}) = %s",
	position->page, position->offset, eb_error_string(EB_SUCCESS)));
    eb_unlock(&book->lock);

    return EB_SUCCESS;


  failed:
    eb_invalidate_text_context(book);
    LOG(("out: eb_seek_text() = %s", eb_error_string(error_code)));
    eb_unlock(&book->lock);
    return error_code;
}
