getRandomArray(AHB_Seller_Config& config, RandomArray& ra, const std::vector<std::vector<uint32> >& addedItem)
{
    ra.clear();
    bool Ok = false;

    for (uint32 j = 0; j < MAX_AUCTION_QUALITY; ++j)
    {
        for (uint32 i = 0; i < MAX_ITEM_CLASS; ++i)
        {
            if ((config.GetMissedItemsPerClass(AuctionQuality(j), ItemClass(i)) > addedItem[j][i]) && !m_ItemPool[j][i].empty())
            {
                RandomArrayEntry miss_item;
                miss_item.color = j;
                miss_item.itemclass = i;
                ra.push_back(miss_item);
                Ok = true;
            }
        }
    }
    return Ok;
}
