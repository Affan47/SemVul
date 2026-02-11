deleteRange()
{
    if (dateRangeTree->selectedItems().count() != 1) return;
    int index = allDateRanges->indexOfChild(dateRangeTree->selectedItems().first());


    delete allDateRanges->takeChild(index);
    seasons->deleteSeason(index);
}
