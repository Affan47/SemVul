HasMechanic(uint32 mechanic) const
{
    return GetSpellProto()->Mechanic == mechanic ||
           GetSpellProto()->EffectMechanic[m_effIndex] == mechanic;
}
