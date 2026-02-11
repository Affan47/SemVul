HandleMirrorName(bool apply, bool Real)
{
    if (!Real)
        return;

    Unit* caster = GetCaster();
    Unit* target = GetTarget();

    if (!target || !caster || target->GetTypeId() != TYPEID_UNIT)
        return;

    if (apply)
        target->SetName(caster->GetName());
    else
    {
        CreatureInfo const* cinfo = ((Creature*)target)->GetCreatureInfo();
        if (!cinfo)
            return;

        target->SetName(cinfo->Name);
    }
}
