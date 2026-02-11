DoFleeToGetAssistance()
{
    if (!getVictim())
        { return; }

    float radius = sWorld.getConfig(CONFIG_FLOAT_CREATURE_FAMILY_FLEE_ASSISTANCE_RADIUS);
    if (radius > 0)
    {
        Creature* pCreature = NULL;

        MaNGOS::NearestAssistCreatureInCreatureRangeCheck u_check(this, getVictim(), radius);
        MaNGOS::CreatureLastSearcher<MaNGOS::NearestAssistCreatureInCreatureRangeCheck> searcher(pCreature, u_check);
        Cell::VisitGridObjects(this, searcher, radius);

        SetNoSearchAssistance(true);
        UpdateSpeed(MOVE_RUN, false);

        if (!pCreature)
            { SetFeared(true, getVictim()->GetObjectGuid(), 0 , sWorld.getConfig(CONFIG_UINT32_CREATURE_FAMILY_FLEE_DELAY)); }
        else
        {
            SetTargetGuid(ObjectGuid());
            GetMotionMaster()->MoveSeekAssistance(pCreature->GetPositionX(), pCreature->GetPositionY(), pCreature->GetPositionZ());
        }
    }
}
