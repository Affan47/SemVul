CancelGlobalCooldown()
{
    if (!m_spellInfo->StartRecoveryTime)
        { return; }


    if (m_caster->GetCurrentSpell(CURRENT_GENERIC_SPELL) != this)
        { return; }


    if (m_caster->GetCharmInfo())
        { m_caster->GetCharmInfo()->GetGlobalCooldownMgr().CancelGlobalCooldown(m_spellInfo); }
    else if (m_caster->GetTypeId() == TYPEID_PLAYER)
        { ((Player*)m_caster)->GetGlobalCooldownMgr().CancelGlobalCooldown(m_spellInfo); }
}
