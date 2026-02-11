AttackStart(Unit* u)
{
    if (!u || (m_creature->IsPet() && ((Pet*)m_creature)->getPetType() == MINI_PET))
        { return; }

    if (m_creature->Attack(u, true))
    {


        HandleMovementOnAttackStart(u);
        inCombat = true;
    }
}
