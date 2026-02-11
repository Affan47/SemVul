MoveInLineOfSight(Unit* u)
{

    if (!m_creature->CanFly() && m_creature->GetDistanceZ(u) > CREATURE_Z_ATTACK_RANGE)
        { return; }

    if (!m_creature->getVictim() && u->IsTargetableForAttack() &&
        (u->IsHostileToPlayers() || m_creature->IsHostileTo(u) ) &&
        u->isInAccessablePlaceFor(m_creature))
    {
        float attackRadius = m_creature->GetAttackDistance(u);
        if (m_creature->IsWithinDistInMap(u, attackRadius))
        {

            AttackStart(u);
            u->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);
        }
    }
}
