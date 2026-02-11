setSortCallback(SortCallback cb)
{
    if (d_sortCallback != cb)
    {
        d_sortCallback = cb;
        if (d_sortEnabled && !d_initialising)
        {
            sortList();
        }
        handleUpdatedItemData(true);
    }
}
