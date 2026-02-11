dom_tree_to_split(xmlNodePtr node, QofBook *book)
{
    struct split_pdata pdata;
    Split *ret;

    g_return_val_if_fail (book, NULL);

    ret = xaccMallocSplit(book);
    g_return_val_if_fail(ret, NULL);

    pdata.split = ret;
    pdata.book = book;


    if (dom_tree_generic_parse(node, spl_dom_handlers, &pdata))
    {
        return ret;
    }
    else
    {
        xaccSplitDestroy(ret);
        return NULL;
    }
}
