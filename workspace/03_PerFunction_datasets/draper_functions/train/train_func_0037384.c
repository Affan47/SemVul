eb_booklist_book_count(EB_BookList *booklist, int *book_count)
{
    EB_Error_Code error_code;

    eb_lock(&booklist->lock);
    LOG(("in: eb_booklist_book_count(booklist=%d)", (int)booklist->code));

    if (booklist->entries == NULL) {
	error_code = EB_ERR_UNBOUND_BOOKLIST;
	goto failed;
    }
    *book_count = booklist->entry_count;

    LOG(("out: eb_booklist_book_count(count=%d) = %s", *book_count,
	eb_error_string(EB_SUCCESS)));
    eb_unlock(&booklist->lock);
    return EB_SUCCESS;


  failed:
    LOG(("out: eb_booklist_book_count() = %s", eb_error_string(error_code)));
    eb_unlock(&booklist->lock);
    return error_code;
}
