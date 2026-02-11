EffectGravityPull(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;

    float x, y, z;
    if (m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION)
        m_targets.getDestination(x, y, z);
    else
        m_caster->GetPosition(x, y, z);

    float speed = float(m_spellInfo->EffectMiscValue[eff_idx]) * 0.15f;
    float height = float(unitTarget->GetDistance(x, y, z) * 0.2f);

    unitTarget->GetMotionMaster()->MoveJump(x, y, z, speed, height);
}
