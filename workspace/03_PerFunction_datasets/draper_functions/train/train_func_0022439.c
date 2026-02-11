WriteAmmoToPacket(WorldPacket* data)
{
    uint32 ammoInventoryType = 0;
    uint32 ammoDisplayID = 0;

    if (m_caster->GetTypeId() == TYPEID_PLAYER)
    {
        Item* pItem = ((Player*)m_caster)->GetWeaponForAttack(RANGED_ATTACK);
        if (pItem)
        {
            ammoInventoryType = pItem->GetProto()->InventoryType;
            if (ammoInventoryType == INVTYPE_THROWN)
                ammoDisplayID = pItem->GetProto()->DisplayInfoID;
            else
            {
                uint32 ammoID = ((Player*)m_caster)->GetUInt32Value(PLAYER_AMMO_ID);
                if (ammoID)
                {
                    ItemPrototype const* pProto = ObjectMgr::GetItemPrototype(ammoID);
                    if (pProto)
                    {
                        ammoDisplayID = pProto->DisplayInfoID;
                        ammoInventoryType = pProto->InventoryType;
                    }
                }
                else if (m_caster->GetDummyAura(46699))
                {
                    ammoDisplayID = 5996;
                    ammoInventoryType = INVTYPE_AMMO;
                }
            }
        }
    }
    else
    {
        for (uint8 i = 0; i < MAX_VIRTUAL_ITEM_SLOT; ++i)
        {
            if (uint32 item_id = m_caster->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + i))
            {
                if (ItemEntry const* itemEntry = sItemStore.LookupEntry(item_id))
                {
                    if (itemEntry->Class == ITEM_CLASS_WEAPON)
                    {
                        switch (itemEntry->SubClass)
                        {
                            case ITEM_SUBCLASS_WEAPON_THROWN:
                                ammoDisplayID = itemEntry->DisplayId;
                                ammoInventoryType = itemEntry->InventoryType;
                                break;
                            case ITEM_SUBCLASS_WEAPON_BOW:
                            case ITEM_SUBCLASS_WEAPON_CROSSBOW:
                                ammoDisplayID = 5996;
                                ammoInventoryType = INVTYPE_AMMO;
                                break;
                            case ITEM_SUBCLASS_WEAPON_GUN:
                                ammoDisplayID = 5998;
                                ammoInventoryType = INVTYPE_AMMO;
                                break;
                        }

                        if (ammoDisplayID)
                            break;
                    }
                }
            }
        }
    }

    *data << uint32(ammoDisplayID);
    *data << uint32(ammoInventoryType);
}
