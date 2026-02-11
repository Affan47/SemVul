EffectPickPocket(SpellEffectIndex )
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        { return; }


    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT || m_caster->IsFriendlyTo(unitTarget))
        { return; }


    if (unitTarget->IsAlive() && (unitTarget->GetCreatureTypeMask() & CREATURE_TYPEMASK_HUMANOID_OR_UNDEAD) != 0)
    {
        int32 chance = 10 + int32(m_caster->getLevel()) - int32(unitTarget->getLevel());

        if (chance > irand(0, 19))
        {


            ((Player*)m_caster)->SendLoot(unitTarget->GetObjectGuid(), LOOT_PICKPOCKETING);
        }
        else
        {

            m_caster->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);
            unitTarget->AttackedBy(m_caster);
        }
    }
}
