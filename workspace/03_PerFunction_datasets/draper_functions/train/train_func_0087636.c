IsSingleTargetSpells(SpellEntry const* spellInfo1, SpellEntry const* spellInfo2)
{


    if (spellInfo1->SpellFamilyName == spellInfo2->SpellFamilyName &&
            spellInfo1->SpellIconID == spellInfo2->SpellIconID)
        return true;


    SpellSpecific spec1 = GetSpellSpecific(spellInfo1->Id);

    switch (spec1)
    {
        case SPELL_JUDGEMENT:
        case SPELL_MAGE_POLYMORPH:
            if (GetSpellSpecific(spellInfo2->Id) == spec1)
                return true;
            break;
        default:
            break;
    }

    return false;
}
