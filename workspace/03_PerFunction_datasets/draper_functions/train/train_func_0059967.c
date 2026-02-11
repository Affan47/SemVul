EffectQuestComplete(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;


    switch (m_spellInfo->Id)
    {
        case 43458:
        {
            if (!unitTarget->HasAura(m_spellInfo->CalculateSimpleValue(eff_idx)))
                return;

            break;
        }


        default:
            break;
    }

    uint32 quest_id = m_spellInfo->EffectMiscValue[eff_idx];
    ((Player*)unitTarget)->AreaExploredOrEventHappens(quest_id);
}
