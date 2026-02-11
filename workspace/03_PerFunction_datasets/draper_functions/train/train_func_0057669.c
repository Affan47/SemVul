eb_subbook_title(EB_Book *book, char *title)
{
    EB_Error_Code error_code;

    eb_lock(&book->lock);
    LOG(("in: eb_subbook_title(book=%d)", (int)book->code));


    if (book->subbook_current == NULL) {
	error_code = EB_ERR_NO_CUR_SUB;
	goto failed;
    }

    strcpy(title, book->subbook_current->title);

    LOG(("out: eb_subbook_title(title=%s) = %s", title,
	eb_error_string(EB_SUCCESS)));
    eb_unlock(&book->lock);

    return EB_SUCCESS;


  failed:
    *title = '\0';
    LOG(("out: eb_subbook_title() = %s", eb_error_string(error_code)));
    eb_unlock(&book->lock);
    return error_code;
}
