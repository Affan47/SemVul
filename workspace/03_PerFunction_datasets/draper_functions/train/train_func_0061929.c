setAcceptTradeMode(TradeData* myTrade, TradeData* hisTrade, Item** myItems, Item** hisItems)
{
    myTrade->SetInAcceptProcess(true);
    hisTrade->SetInAcceptProcess(true);


    for (int i = 0; i < TRADE_SLOT_TRADED_COUNT; ++i)
    {
        if (Item* item = myTrade->GetItem(TradeSlots(i)))
        {
            DEBUG_LOG("player trade %s bag: %u slot: %u", item->GetGuidStr().c_str(), item->GetBagSlot(), item->GetSlot());

            myItems[i] = item;
            myItems[i]->SetInTrade();
        }

        if (Item* item = hisTrade->GetItem(TradeSlots(i)))
        {
            DEBUG_LOG("partner trade %s bag: %u slot: %u", item->GetGuidStr().c_str(), item->GetBagSlot(), item->GetSlot());
            hisItems[i] = item;
            hisItems[i]->SetInTrade();
        }
    }
}
