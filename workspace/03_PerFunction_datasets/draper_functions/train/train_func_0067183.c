HandleAuraModRoot(bool apply, bool Real)
{

    if (!Real)
        { return; }

    Unit* target = GetTarget();

    if (apply)
    {

        if (GetSpellSchoolMask(GetSpellProto()) & SPELL_SCHOOL_MASK_FROST)
            { target->ModifyAuraState(AURA_STATE_FROZEN, apply); }

        target->addUnitState(UNIT_STAT_ROOT);

        if (target->GetTypeId() == TYPEID_PLAYER)
        {
            target->SetRoot(true);


            ((Player*)target)->m_movementInfo.SetMovementFlags(MOVEFLAG_MOVE_STOP);
        }
        else
            { target->StopMoving(); }
    }
    else
    {

        if (GetSpellSchoolMask(GetSpellProto()) & SPELL_SCHOOL_MASK_FROST)
        {
            bool found_another = false;
            for (AuraType const* itr = &frozenAuraTypes[0]; *itr != SPELL_AURA_NONE; ++itr)
            {
                Unit::AuraList const& auras = target->GetAurasByType(*itr);
                for (Unit::AuraList::const_iterator i = auras.begin(); i != auras.end(); ++i)
                {
                    if (GetSpellSchoolMask((*i)->GetSpellProto()) & SPELL_SCHOOL_MASK_FROST)
                    {
                        found_another = true;
                        break;
                    }
                }
                if (found_another)
                    { break; }
            }

            if (!found_another)
                { target->ModifyAuraState(AURA_STATE_FROZEN, apply); }
        }


        if (target->HasAuraType(SPELL_AURA_MOD_ROOT))
            { return; }

        target->clearUnitState(UNIT_STAT_ROOT);

        if (!target->hasUnitState(UNIT_STAT_STUNNED) && (target->GetTypeId() == TYPEID_PLAYER))
            { target->SetRoot(false); }
    }
}
