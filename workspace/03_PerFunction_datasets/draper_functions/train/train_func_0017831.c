HandlePreventFleeing(bool apply, bool Real)
{
    if (!Real)
        { return; }

    Unit::AuraList const& fearAuras = GetTarget()->GetAurasByType(SPELL_AURA_MOD_FEAR);
    if (!fearAuras.empty())
    {
        if (apply)
            { GetTarget()->SetFeared(false, fearAuras.front()->GetCasterGuid()); }
        else
            { GetTarget()->SetFeared(true); }
    }
}
