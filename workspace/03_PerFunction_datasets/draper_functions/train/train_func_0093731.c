EffectInstaKill(SpellEffectIndex )
{
    if (!unitTarget || !unitTarget->isAlive())
        return;

    if (m_caster == unitTarget)
        finish();

    WorldObject* caster = GetCastingObject();

    WorldPacket data(SMSG_SPELLINSTAKILLLOG, (8 + 8 + 4));
    data << (caster && caster->GetTypeId() != TYPEID_GAMEOBJECT ? m_caster->GetObjectGuid() : ObjectGuid());
    data << unitTarget->GetObjectGuid();
    data << uint32(m_spellInfo->Id);
    m_caster->SendMessageToSet(&data, true);

    m_caster->DealDamage(unitTarget, unitTarget->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
}
