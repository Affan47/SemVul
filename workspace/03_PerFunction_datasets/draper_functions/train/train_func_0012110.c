ClearTemporaryFaction()
{


    if (IsCharmed())
        { return; }


    setFaction(GetCreatureInfo()->FactionAlliance);

    if (m_temporaryFactionFlags & TEMPFACTION_TOGGLE_NON_ATTACKABLE && GetCreatureInfo()->UnitFlags & UNIT_FLAG_NON_ATTACKABLE)
        { SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE); }
    if (m_temporaryFactionFlags & TEMPFACTION_TOGGLE_OOC_NOT_ATTACK && GetCreatureInfo()->UnitFlags & UNIT_FLAG_OOC_NOT_ATTACKABLE && !IsInCombat())
        { SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE); }
    if (m_temporaryFactionFlags & TEMPFACTION_TOGGLE_PASSIVE && GetCreatureInfo()->UnitFlags & UNIT_FLAG_PASSIVE)
        { SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE); }

    m_temporaryFactionFlags = TEMPFACTION_NONE;
}
