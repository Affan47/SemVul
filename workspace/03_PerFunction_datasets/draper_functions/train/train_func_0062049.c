EffectSanctuary(SpellEffectIndex )
{
    if (!unitTarget)
        { return; }


    unitTarget->CombatStop();
    unitTarget->GetHostileRefManager().deleteReferences();


    if (m_spellInfo->IsFitToFamily(SPELLFAMILY_ROGUE, UI64LIT(0x0000000000000800)))
        { ((Player*)m_caster)->RemoveSpellsCausingAura(SPELL_AURA_MOD_ROOT); }
}
