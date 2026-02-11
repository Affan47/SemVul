xaccAccountScrubSplits (Account *account)
{
    GList *node;

    for (node = xaccAccountGetSplitList (account); node; node = node->next)
        xaccSplitScrub (node->data);
}
