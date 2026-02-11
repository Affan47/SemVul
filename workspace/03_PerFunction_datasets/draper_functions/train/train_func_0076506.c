eb_subbook_title2(EB_Book *book, EB_Subbook_Code subbook_code, char *title)
{
    EB_Error_Code error_code;

    eb_lock(&book->lock);
    LOG(("in: eb_subbook_title2(book=%d, subbook_code=%d)",
	(int)book->code, (int)subbook_code));


    if (book->path == NULL) {
	error_code = EB_ERR_UNBOUND_BOOK;
	goto failed;
    }


    if (subbook_code < 0 || book->subbook_count <= subbook_code) {
	error_code = EB_ERR_NO_SUCH_SUB;
	goto failed;
    }

    strcpy(title, (book->subbooks + subbook_code)->title);

    LOG(("out: eb_subbook_title2(title=%s) = %s", title,
	eb_error_string(EB_SUCCESS)));
    eb_unlock(&book->lock);

    return EB_SUCCESS;


  failed:
    *title = '\0';
    LOG(("out: eb_subbook_title2() = %s", eb_error_string(error_code)));
    eb_unlock(&book->lock);
    return error_code;
}
