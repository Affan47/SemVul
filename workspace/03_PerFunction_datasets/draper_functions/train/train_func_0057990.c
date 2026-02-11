TakePower()
{
    if (m_CastItem || m_triggeredByAuraSpell)
        return;


    if (m_spellInfo->powerType == POWER_HEALTH)
    {
        m_caster->ModifyHealth(-(int32)m_powerCost);
        return;
    }

    if (m_spellInfo->powerType >= MAX_POWERS)
    {
        sLog.outError("Spell::TakePower: Unknown power type '%d'", m_spellInfo->powerType);
        return;
    }

    Powers powerType = Powers(m_spellInfo->powerType);

    if (powerType == POWER_RUNE)
    {
        CheckOrTakeRunePower(true);
        return;
    }

    m_caster->ModifyPower(powerType, -(int32)m_powerCost);


    if (powerType == POWER_MANA && m_powerCost > 0)
        m_caster->SetLastManaUse();
}
