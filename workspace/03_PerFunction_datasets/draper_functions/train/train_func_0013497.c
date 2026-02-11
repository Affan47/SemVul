Finalize(Unit& unit)
{
    if (unit.GetTypeId() != TYPEID_UNIT)
        return;

    if (((Creature&)unit).AI() && unit.movespline->Finalized())
        ((Creature&)unit).AI()->MovementInform(EFFECT_MOTION_TYPE, m_Id);

    if (unit.isAlive() && !unit.hasUnitState(UNIT_STAT_CONFUSED | UNIT_STAT_FLEEING | UNIT_STAT_NO_COMBAT_MOVEMENT))
    {
        if (Unit* victim = unit.getVictim())
            unit.GetMotionMaster()->MoveChase(victim);
        else
            unit.GetMotionMaster()->Initialize();
    }
}
