CloneItem(uint32 count, Player const* player) const
{
    Item* newItem = CreateItem(GetEntry(), count, player, GetItemRandomPropertyId());
    if (!newItem)
        return NULL;

    newItem->SetGuidValue(ITEM_FIELD_CREATOR,     GetGuidValue(ITEM_FIELD_CREATOR));
    newItem->SetGuidValue(ITEM_FIELD_GIFTCREATOR, GetGuidValue(ITEM_FIELD_GIFTCREATOR));
    newItem->SetUInt32Value(ITEM_FIELD_FLAGS,     GetUInt32Value(ITEM_FIELD_FLAGS));
    newItem->SetUInt32Value(ITEM_FIELD_DURATION,  GetUInt32Value(ITEM_FIELD_DURATION));
    return newItem;
}
