_StoreItem(uint8 tab, uint8 slot, Item* pItem, uint32 count, bool clone)
{
    if (!pItem)
        return NULL;

    DEBUG_LOG("GUILD STORAGE: StoreItem tab = %u, slot = %u, item = %u, count = %u", tab, slot, pItem->GetEntry(), count);

    Item* pItem2 = m_TabListMap[tab]->Slots[slot];

    if (!pItem2)
    {
        if (clone)
            pItem = pItem->CloneItem(count);
        else
            pItem->SetCount(count);

        if (!pItem)
            return NULL;

        m_TabListMap[tab]->Slots[slot] = pItem;

        pItem->SetGuidValue(ITEM_FIELD_CONTAINED, ObjectGuid());
        pItem->SetGuidValue(ITEM_FIELD_OWNER, ObjectGuid());
        AddGBankItemToDB(GetId(), tab, slot, pItem->GetGUIDLow(), pItem->GetEntry());
        pItem->FSetState(ITEM_NEW);
        pItem->SaveToDB();

        return pItem;
    }
    else
    {
        pItem2->SetCount(pItem2->GetCount() + count);
        pItem2->FSetState(ITEM_CHANGED);
        pItem2->SaveToDB();

        if (!clone)
        {
            pItem->RemoveFromWorld();
            pItem->DeleteFromDB();
            delete pItem;
        }

        return pItem2;
    }
}
