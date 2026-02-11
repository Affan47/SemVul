findItemWithIDFromList(const LBItemList &itemList, uint searchID, const TreeItem* startItem, bool foundStartItem)
{
    size_t itemCount = itemList.size();

    for (size_t index = 0; index < itemCount; ++index)
    {
        if (foundStartItem == true)
        {

            if (itemList[index]->getID() == searchID)
                return itemList[index];
        }
        else
        {

            if (itemList[index] == startItem)
                foundStartItem = true;
        }

        if (itemList[index]->getItemCount() > 0)
        {

            TreeItem *foundSelectedTree;
            foundSelectedTree = findItemWithIDFromList(itemList[index]->getItemList(), searchID, startItem, foundStartItem);
            if (foundSelectedTree != 0)
                return foundSelectedTree;
        }
    }

    return 0;
}
