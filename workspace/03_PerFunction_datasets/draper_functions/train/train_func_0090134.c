HandlePeriodicHeal(bool apply, bool )
{
    m_isPeriodic = apply;

    Unit* target = GetTarget();


    bool loading = (target->GetTypeId() == TYPEID_PLAYER && ((Player*)target)->GetSession()->PlayerLoading());


    if (apply)
    {
        if (loading)
            return;

        Unit* caster = GetCaster();
        if (!caster)
            return;


        if (GetSpellProto()->SpellIconID == 329 && GetSpellProto()->SpellVisual[0] == 7625)
        {
            int32 ap = int32(0.22f * caster->GetTotalAttackPowerValue(BASE_ATTACK));
            int32 holy = caster->SpellBaseDamageBonusDone(GetSpellSchoolMask(GetSpellProto()));
            if (holy < 0)
                holy = 0;
            holy = int32(holy * 377 / 1000);
            m_modifier.m_amount += ap > holy ? ap : holy;
        }

        else if (GetSpellProto()->SpellIconID == 3088 && GetSpellProto()->SpellVisual[0] == 8145)
        {
            int32 healthBonus = int32(0.0032f * caster->GetMaxHealth());
            m_modifier.m_amount += healthBonus;
        }

        m_modifier.m_amount = caster->SpellHealingBonusDone(target, GetSpellProto(), m_modifier.m_amount, DOT, GetStackAmount());


        if (GetSpellProto()->IsFitToFamily(SPELLFAMILY_DRUID, UI64LIT(0x0000000000000010)))
            if (caster->HasAura(64760))
                caster->CastCustomSpell(target, 64801, &m_modifier.m_amount, NULL, NULL, true, NULL);
    }
}
