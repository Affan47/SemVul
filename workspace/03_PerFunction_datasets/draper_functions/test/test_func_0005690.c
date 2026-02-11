HandleAuraModDispelResist(bool apply, bool Real)
{
    if (!Real || !apply)
        return;

    if (GetId() == 33206)
        GetTarget()->CastSpell(GetTarget(), 44416, true, NULL, this, GetCasterGuid());
}
