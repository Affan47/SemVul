prepare(SpellCastTargets const* targets, Aura* triggeredByAura)
{
    m_targets = *targets;

    m_spellState = SPELL_STATE_PREPARING;

    m_castPositionX = m_caster->GetPositionX();
    m_castPositionY = m_caster->GetPositionY();
    m_castPositionZ = m_caster->GetPositionZ();
    m_castOrientation = m_caster->GetOrientation();

    if (triggeredByAura)
        { m_triggeredByAuraSpell  = triggeredByAura->GetSpellProto(); }


    SpellEvent* Event = new SpellEvent(this);
    m_caster->m_Events.AddEvent(Event, m_caster->m_Events.CalculateTime(1));


    if (!m_IsTriggeredSpell && m_caster->IsNonMeleeSpellCasted(false, true, true))
    {
        SendCastResult(SPELL_FAILED_SPELL_IN_PROGRESS);
        finish(false);
        return;
    }


    m_powerCost = CalculatePowerCost(m_spellInfo, m_caster, this, m_CastItem);

    SpellCastResult result = CheckCast(true);
    if (result != SPELL_CAST_OK && !IsAutoRepeat())
    {
        if (triggeredByAura)
        {
            SendChannelUpdate(0);
            triggeredByAura->GetHolder()->SetAuraDuration(0);
        }
        SendCastResult(result);
        finish(false);
        return;
    }


    prepareDataForTriggerSystem();


    m_casttime = GetSpellCastTime(m_spellInfo, this);
    m_duration = CalculateSpellDuration(m_spellInfo, m_caster);


    ReSetTimer();


    if (!m_IsTriggeredSpell && isSpellBreakStealth(m_spellInfo))
    {
        m_caster->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);
        m_caster->RemoveSpellsCausingAura(SPELL_AURA_FEIGN_DEATH);
    }


    if (!m_IsTriggeredSpell)
    {

        m_caster->SetCurrentCastedSpell(this);


        SendSpellStart();

        TriggerGlobalCooldown();
    }

    else if (m_timer == 0)
        { cast(true); }


}
