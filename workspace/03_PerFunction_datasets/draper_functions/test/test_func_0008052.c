SendItem(Player* pReceiver)
    {
        if (pReceiver->HasItemCount(ITEM_BOOK_AQUOR, 1) &&
            pReceiver->HasItemCount(ITEM_SILVERY_CLAWS, 11) &&
            pReceiver->HasItemCount(ITEM_IRONTREE_HEART, 1) &&
            !pReceiver->HasItemCount(ITEM_SILVER_TOTEM, 1))
        {
            if (Item* pItem = pReceiver->StoreNewItemInInventorySlot(ITEM_SILVER_TOTEM, 1))
            {
                pReceiver->SendNewItem(pItem, 1, true, false);
            }
        }
    }
