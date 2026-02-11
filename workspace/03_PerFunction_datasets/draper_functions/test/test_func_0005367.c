xaccAccountTreeScrubQuoteSources (Account *root, gnc_commodity_table *table)
{
    gboolean new_style = FALSE;
    ENTER(" ");

    if (!root || !table)
    {
        LEAVE("Oops");
        return;
    }

    gnc_commodity_table_foreach_commodity (table, check_quote_source, &new_style);

    move_quote_source(root, GINT_TO_POINTER(new_style));
    gnc_account_foreach_descendant (root, move_quote_source,
                                    GINT_TO_POINTER(new_style));
    LEAVE("Migration done");
}
