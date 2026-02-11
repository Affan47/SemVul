UpdateVendorItemCurrentCount(VendorItem const* vItem, uint32 used_count)
{
    if (!vItem->maxcount)
        return 0;

    VendorItemCounts::iterator itr = m_vendorItemCounts.begin();
    for (; itr != m_vendorItemCounts.end(); ++itr)
        if (itr->itemId == vItem->item)
            break;

    if (itr == m_vendorItemCounts.end())
    {
        uint32 new_count = vItem->maxcount > used_count ? vItem->maxcount - used_count : 0;
        m_vendorItemCounts.push_back(VendorItemCount(vItem->item, new_count));
        return new_count;
    }

    VendorItemCount* vCount = &*itr;

    time_t ptime = time(NULL);

    if (vCount->lastIncrementTime + vItem->incrtime <= ptime)
    {
        ItemPrototype const* pProto = ObjectMgr::GetItemPrototype(vItem->item);

        uint32 diff = uint32((ptime - vCount->lastIncrementTime) / vItem->incrtime);
        if ((vCount->count + diff * pProto->BuyCount) < vItem->maxcount)
            vCount->count += diff * pProto->BuyCount;
        else
            vCount->count = vItem->maxcount;
    }

    vCount->count = vCount->count > used_count ? vCount->count - used_count : 0;
    vCount->lastIncrementTime = ptime;
    return vCount->count;
}
