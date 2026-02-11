removeItem(InventoryItem& item)
{
    if (item.getParent() != this ||
        item.locationOnReceiverX() == -1 ||
        item.locationOnReceiverY() == -1)
            return;

    eraseItemFromContentMap(item);
    item.setLocationOnReceiver(-1, -1);
    removeChildWindow(&item);
}
