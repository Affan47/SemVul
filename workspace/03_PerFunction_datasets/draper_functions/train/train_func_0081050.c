HandleAuctionItemCommand(char* args)
{

    char* typeStr = ExtractLiteralArg(&args);
    if (!typeStr)
        return false;

    uint32 houseid;
    if (strncmp(typeStr, "alliance", strlen(typeStr)) == 0)
        houseid = 1;
    else if (strncmp(typeStr, "horde", strlen(typeStr)) == 0)
        houseid = 6;
    else if (strncmp(typeStr, "goblin", strlen(typeStr)) == 0)
        houseid = 7;
    else
        return false;


    char* itemStr = ExtractArg(&args);
    if (!itemStr)
        return false;

    uint32 item_id = 0;
    uint32 item_count = 1;
    if (sscanf(itemStr, "%u:%u", &item_id, &item_count) != 2)
        if (sscanf(itemStr, "%u", &item_id) != 1)
            return false;

    uint32 price;
    if (!ExtractUInt32(&args, price))
        return false;

    uint32 buyout;
    if (!ExtractOptUInt32(&args, buyout, 0))
        return false;

    uint32 etime = 4 * MIN_AUCTION_TIME;
    if (char* timeStr = ExtractLiteralArg(&args))
    {
        if (strncmp(timeStr, "short", strlen(timeStr)) == 0)
            etime = 1 * MIN_AUCTION_TIME;
        else if (strncmp(timeStr, "long", strlen(timeStr)) == 0)
            etime = 2 * MIN_AUCTION_TIME;
        else if (strncmp(timeStr, "verylong", strlen(timeStr)) == 0)
            etime = 4 * MIN_AUCTION_TIME;
        else
            return false;
    }

    AuctionHouseEntry const* auctionHouseEntry = sAuctionHouseStore.LookupEntry(houseid);
    AuctionHouseObject* auctionHouse = sAuctionMgr.GetAuctionsMap(auctionHouseEntry);

    if (!item_id)
    {
        PSendSysMessage(LANG_COMMAND_ITEMIDINVALID, item_id);
        SetSentErrorMessage(true);
        return false;
    }

    ItemPrototype const* item_proto = ObjectMgr::GetItemPrototype(item_id);
    if (!item_proto)
    {
        PSendSysMessage(LANG_COMMAND_ITEMIDINVALID, item_id);
        SetSentErrorMessage(true);
        return false;
    }

    if (item_count < 1 || (item_proto->MaxCount > 0 && item_count > uint32(item_proto->MaxCount)))
    {
        PSendSysMessage(LANG_COMMAND_INVALID_ITEM_COUNT, item_count, item_id);
        SetSentErrorMessage(true);
        return false;
    }

    do
    {
        uint32 item_stack = item_count > item_proto->GetMaxStackSize() ? item_proto->GetMaxStackSize() : item_count;
        item_count -= item_stack;

        Item* newItem = Item::CreateItem(item_id, item_stack);
        MANGOS_ASSERT(newItem);

        auctionHouse->AddAuction(auctionHouseEntry, newItem, etime, price, buyout);
    }
    while (item_count);

    return true;
}
