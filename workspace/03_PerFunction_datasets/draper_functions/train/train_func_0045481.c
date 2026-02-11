dom_tree_to_book (xmlNodePtr node, QofBook *book)
{
    gboolean successful;

    successful = dom_tree_generic_parse (node, book_handlers_v2,
                                         book);
    if (!successful)
    {
        PERR ("failed to parse book");
        book = NULL;
    }

    return book;
}
