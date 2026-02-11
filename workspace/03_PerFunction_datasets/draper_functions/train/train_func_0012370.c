_setMembersGroup(ObjectGuid guid, uint8 group)
{
    member_witerator slot = _getMemberWSlot(guid);
    if (slot == m_memberSlots.end())
        { return false; }

    slot->group = group;

    SubGroupCounterIncrease(group);

    if (!isBGGroup())
        { CharacterDatabase.PExecute("UPDATE group_member SET subgroup='%u' WHERE memberGuid='%u'", group, guid.GetCounter()); }

    return true;
}
