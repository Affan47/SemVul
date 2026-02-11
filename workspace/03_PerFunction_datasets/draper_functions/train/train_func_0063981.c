SetLootRecipient(Unit* unit)
{


    if (!unit)
    {
        m_lootRecipientGuid.Clear();
        m_lootGroupRecipientId = 0;
        RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_TAPPED);
        RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_TAPPED_BY_PLAYER);
        return;
    }

    Player* player = unit->GetCharmerOrOwnerPlayerOrPlayerItself();
    if (!player)
        return;


    m_lootRecipientGuid = player->GetObjectGuid();


    if (Group* group = player->GetGroup())
        m_lootGroupRecipientId = group->GetId();

    SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_TAPPED);
    SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_TAPPED_BY_PLAYER);
}
