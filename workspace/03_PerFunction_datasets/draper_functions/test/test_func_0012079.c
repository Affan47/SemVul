EffectDestroyAllTotems(SpellEffectIndex )
{
    for (int slot = 0;  slot < MAX_TOTEM_SLOT; ++slot)
        if (Totem* totem = m_caster->GetTotem(TotemSlot(slot)))
            { totem->UnSummon(); }
}
