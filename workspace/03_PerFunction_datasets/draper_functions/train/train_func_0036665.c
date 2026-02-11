get_random_price(QofBook *book)
{
    GNCPrice *p;

    p = gnc_price_create (book);
    if (!p)
    {
        failure_args("engine-stuff", __FILE__, __LINE__,
                     "get_random_price failed");
        return NULL;
    }

    make_random_changes_to_price (book, p);
    if (!p)
    {
        failure_args("engine-stuff", __FILE__, __LINE__,
                     "make_random_changes_to_price failed");
        return NULL;
    }

    return p;
}
