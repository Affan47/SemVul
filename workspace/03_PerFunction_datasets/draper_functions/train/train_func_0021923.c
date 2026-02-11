HandleSchoolAbsorb(bool apply, bool Real)
{
    if (!Real)
        { return; }

    Unit* caster = GetCaster();
    if (!caster)
        { return; }

    Unit* target = GetTarget();
    SpellEntry const* spellProto = GetSpellProto();
    if (apply)
    {

        if (target->GetTypeId() != TYPEID_PLAYER || !((Player*)target)->GetSession()->PlayerLoading())
        {
            float DoneActualBenefit = 0.0f;
            switch (spellProto->SpellFamilyName)
            {
                case SPELLFAMILY_PRIEST:

                    if (spellProto->SpellFamilyFlags & UI64LIT(0x0000000000000001))
                    {

                        DoneActualBenefit = caster->SpellBaseHealingBonusDone(GetSpellSchoolMask(spellProto)) * 0.3f;
                        break;
                    }
                    break;
                case SPELLFAMILY_MAGE:

                    if (spellProto->IsFitToFamilyMask(UI64LIT(0x0000000100080108)))

                        { DoneActualBenefit = caster->SpellBaseDamageBonusDone(GetSpellSchoolMask(spellProto)) * 0.1f; }
                    break;
                case SPELLFAMILY_WARLOCK:

                    if (spellProto->SpellFamilyFlags == UI64LIT(0x00))

                        { DoneActualBenefit = caster->SpellBaseDamageBonusDone(GetSpellSchoolMask(spellProto)) * 0.1f; }
                    break;
                default:
                    break;
            }

            DoneActualBenefit *= caster->CalculateLevelPenalty(GetSpellProto());

            m_modifier.m_amount += (int32)DoneActualBenefit;
        }
    }
}
