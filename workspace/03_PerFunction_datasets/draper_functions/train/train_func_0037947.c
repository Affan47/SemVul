EffectStuck(SpellEffectIndex )
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    if (!sWorld.getConfig(CONFIG_BOOL_CAST_UNSTUCK))
        return;

    Player* pTarget = (Player*)unitTarget;

    DEBUG_LOG("Spell Effect: Stuck");
    DETAIL_LOG("Player %s (guid %u) used auto-unstuck future at map %u (%f, %f, %f)", pTarget->GetName(), pTarget->GetGUIDLow(), m_caster->GetMapId(), m_caster->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());

    if (pTarget->IsTaxiFlying())
        return;


    pTarget->TeleportToHomebind(unitTarget == m_caster ? TELE_TO_SPELL : 0);


    SpellEntry const* spellInfo = sSpellStore.LookupEntry(8690);
    if (!spellInfo)
        return;
    Spell spell(pTarget, spellInfo, true);
    spell.SendSpellCooldown();
}
