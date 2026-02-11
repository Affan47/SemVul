SendSpellGo()
{

    if (!IsNeedSendToClient())
        { return; }

    DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "Sending SMSG_SPELL_GO id=%u", m_spellInfo->Id);

    uint32 castFlags = CAST_FLAG_UNKNOWN9;
    if (IsRangedSpell())
        { castFlags |= CAST_FLAG_AMMO; }

    WorldPacket data(SMSG_SPELL_GO, 53);

    if (m_CastItem)
        { data << m_CastItem->GetPackGUID(); }
    else
        { data << m_caster->GetPackGUID(); }

    data << m_caster->GetPackGUID();
    data << uint32(m_spellInfo->Id);
    data << uint16(castFlags);

    WriteSpellGoTargets(&data);

    data << m_targets;

    if (castFlags & CAST_FLAG_AMMO)
        { WriteAmmoToPacket(&data); }

    m_caster->SendMessageToSet(&data, true);
}
