sortList(bool relayout)
{
    std::sort(d_listItems.begin(), d_listItems.end(), getRealSortCallback());
    if (relayout)
    {
        layoutItemWidgets();
    }
}
