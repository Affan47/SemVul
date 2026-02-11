eb_fix_misleaded_book(EB_Book *book)
{
    const char * const * misleaded;
    EB_Subbook *subbook;
    int i;

    LOG(("in: eb_fix_misleaded_book(book=%d)", (int)book->code));

    for (misleaded = misleaded_book_table; *misleaded != NULL; misleaded++) {
	if (strcmp(book->subbooks[0].title, *misleaded) == 0) {
	    book->character_code = EB_CHARCODE_JISX0208;
	    for (i = 0, subbook = book->subbooks; i < book->subbook_count;
		 i++, subbook++) {
		eb_jisx0208_to_euc(subbook->title, subbook->title);
	    }
	    break;
	}
    }

    LOG(("out: eb_fix_misleaded_book()"));
}
