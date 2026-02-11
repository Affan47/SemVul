EffectHealthLeech(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;
    if (!unitTarget->isAlive())
        return;

    if (damage < 0)
        return;

    DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "HealthLeech :%i", damage);

    uint32 curHealth = unitTarget->GetHealth();
    damage = m_caster->SpellNonMeleeDamageLog(unitTarget, m_spellInfo->Id, damage);
    if ((int32)curHealth < damage)
        damage = curHealth;

    float multiplier = m_spellInfo->EffectMultipleValue[eff_idx];

    if (Player* modOwner = m_caster->GetSpellModOwner())
        modOwner->ApplySpellMod(m_spellInfo->Id, SPELLMOD_MULTIPLE_VALUE, multiplier);

    int32 heal = int32(damage * multiplier);
    if (m_caster->isAlive())
    {
        heal = m_caster->SpellHealingBonusTaken(m_caster, m_spellInfo, heal, HEAL);

        uint32 absorb = 0;
        m_caster->CalculateHealAbsorb(heal, &absorb);

        m_caster->DealHeal(m_caster, heal - absorb, m_spellInfo, false, absorb);
    }
}
