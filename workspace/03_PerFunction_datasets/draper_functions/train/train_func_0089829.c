CheckPetCast(Unit* target)
{
    if (!m_caster->isAlive())
        return SPELL_FAILED_CASTER_DEAD;

    if (m_caster->IsNonMeleeSpellCasted(false))
        return SPELL_FAILED_SPELL_IN_PROGRESS;
    if (m_caster->isInCombat() && IsNonCombatSpell(m_spellInfo))
        return SPELL_FAILED_AFFECTING_COMBAT;

    if (m_caster->GetTypeId() == TYPEID_UNIT && (((Creature*)m_caster)->IsPet() || m_caster->isCharmed()))
    {

        if (m_caster->GetCharmerOrOwner() && !m_caster->GetCharmerOrOwner()->isAlive())
            return SPELL_FAILED_CASTER_DEAD;

        if (!target && m_targets.getUnitTarget())
            target = m_targets.getUnitTarget();

        bool need = false;
        for (int i = 0; i < MAX_EFFECT_INDEX; ++i)
        {
            if (m_spellInfo->EffectImplicitTargetA[i] == TARGET_CHAIN_DAMAGE ||
                    m_spellInfo->EffectImplicitTargetA[i] == TARGET_SINGLE_FRIEND ||
                    m_spellInfo->EffectImplicitTargetA[i] == TARGET_SINGLE_FRIEND_2 ||
                    m_spellInfo->EffectImplicitTargetA[i] == TARGET_DUELVSPLAYER ||
                    m_spellInfo->EffectImplicitTargetA[i] == TARGET_SINGLE_PARTY ||
                    m_spellInfo->EffectImplicitTargetA[i] == TARGET_CURRENT_ENEMY_COORDINATES)
            {
                need = true;
                if (!target)
                    return SPELL_FAILED_BAD_IMPLICIT_TARGETS;
                break;
            }
        }
        if (need)
            m_targets.setUnitTarget(target);

        Unit* _target = m_targets.getUnitTarget();


        if (_target && m_targets.m_targetMask & TARGET_FLAG_UNIT)
        {
            if (!_target->isTargetableForAttack())
                return SPELL_FAILED_BAD_TARGETS;

            if (IsPositiveSpell(m_spellInfo->Id))
            {
                if (m_caster->IsHostileTo(_target))
                    return SPELL_FAILED_BAD_TARGETS;
            }
            else
            {
                bool duelvsplayertar = false;
                for (int j = 0; j < MAX_EFFECT_INDEX; ++j)
                {

                    duelvsplayertar |= (m_spellInfo->EffectImplicitTargetA[j] == TARGET_DUELVSPLAYER);
                }
                if (m_caster->IsFriendlyTo(target) && !duelvsplayertar)
                {
                    return SPELL_FAILED_BAD_TARGETS;
                }
            }
        }

        if (((Creature*)m_caster)->HasSpellCooldown(m_spellInfo->Id))
            return SPELL_FAILED_NOT_READY;
    }

    return CheckCast(true);
}
