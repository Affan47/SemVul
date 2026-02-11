LoadEquipment(uint32 equip_entry, bool force)
{
    if (equip_entry == 0)
    {
        if (force)
        {
            for (uint8 i = 0; i < MAX_VIRTUAL_ITEM_SLOT; ++i)
                { SetVirtualItem(VirtualItemSlot(i), 0); }
            m_equipmentId = 0;
        }
        return;
    }

    if (EquipmentInfo const* einfo = sObjectMgr.GetEquipmentInfo(equip_entry))
    {
        m_equipmentId = equip_entry;
        for (uint8 i = 0; i < MAX_VIRTUAL_ITEM_SLOT; ++i)
            { SetVirtualItem(VirtualItemSlot(i), einfo->equipentry[i]); }
    }
    else if (EquipmentInfoRaw const* einfo = sObjectMgr.GetEquipmentInfoRaw(equip_entry))
    {
        m_equipmentId = equip_entry;
        for (uint8 i = 0; i < MAX_VIRTUAL_ITEM_SLOT; ++i)
            { SetVirtualItemRaw(VirtualItemSlot(i), einfo->equipmodel[i], einfo->equipinfo[i], einfo->equipslot[i]); }
    }
}
