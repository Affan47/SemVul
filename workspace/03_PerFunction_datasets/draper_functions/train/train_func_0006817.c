SendSpellGo()
{

    if (!IsNeedSendToClient())
        return;

    DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "Sending SMSG_SPELL_GO id=%u", m_spellInfo->Id);

    uint32 castFlags = CAST_FLAG_UNKNOWN9;
    if (IsRangedSpell())
        castFlags |= CAST_FLAG_AMMO;

    if ((m_caster->GetTypeId() == TYPEID_PLAYER) && (m_caster->getClass() == CLASS_DEATH_KNIGHT) && m_spellInfo->runeCostID)
    {
        castFlags |= CAST_FLAG_UNKNOWN19;
        castFlags |= CAST_FLAG_PREDICTED_POWER;
        castFlags |= CAST_FLAG_PREDICTED_RUNES;
    }

    if (m_powerCost)
        castFlags |= CAST_FLAG_PREDICTED_POWER;

    WorldPacket data(SMSG_SPELL_GO, 50);

    if (m_CastItem)
        data << m_CastItem->GetPackGUID();
    else
        data << m_caster->GetPackGUID();

    data << m_caster->GetPackGUID();
    data << uint8(m_cast_count);
    data << uint32(m_spellInfo->Id);
    data << uint32(castFlags);
    data << uint32(WorldTimer::getMSTime());

    WriteSpellGoTargets(&data);

    data << m_targets;

    if (castFlags & CAST_FLAG_PREDICTED_POWER)
        data << uint32(m_caster->GetPower((Powers)m_spellInfo->powerType));

    if (castFlags & CAST_FLAG_PREDICTED_RUNES)
    {
        uint8 v1 = m_runesState;
        uint8 v2 =  m_caster->getClass() == CLASS_DEATH_KNIGHT ? ((Player*)m_caster)->GetRunesState() : 0;
        data << uint8(v1);
        data << uint8(v2);
        for (uint8 i = 0; i < MAX_RUNES; ++i)
        {
            uint8 m = (1 << i);
            if (m & v1)
                if (!(m & v2))
                    data << uint8(0);
        }
    }

    if (castFlags & CAST_FLAG_ADJUST_MISSILE)
    {
        data << float(0);
        data << uint32(0);
    }

    if (castFlags & CAST_FLAG_AMMO)
        WriteAmmoToPacket(&data);

    if (castFlags & CAST_FLAG_VISUAL_CHAIN)
    {
        data << uint32(0);
        data << uint32(0);
    }

    if (m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION)
    {
        data << uint8(0);
    }

    if (m_targets.m_targetMask & TARGET_FLAG_VISUAL_CHAIN)
    {
        data << uint32(0);


    }

    m_caster->SendMessageToSet(&data, true);
}
