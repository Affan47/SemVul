updateGroupSizes(bool hideEmpty)
{
    int i;
    for (i=0; i<groupList->topLevelItemCount(); i++) {
        CostListItem* item = (CostListItem*) groupList->topLevelItem(i);
        int size = (_groupSize.contains(item->costItem())) ?
                   _groupSize[item->costItem()] : -1;
        item->setSize(size);
        item->setHidden(hideEmpty && (size<0));
    }
}
