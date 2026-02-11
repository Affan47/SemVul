AddWall( const gPlayerWall * wall, REAL timeBuilt, gCycleMovement * thisCycle )
{

    if ( sn_GetNetState() == nCLIENT )
        return;

    if ( !wall )
        return;


    gCycle *cycle = wall->Cycle();
    if ( !cycle )
        return;


    if ( thisCycle == cycle )
        return;

    REAL time = timeBuilt;
    if ( thisCycle )
    {
        REAL currentTime = thisCycle->LastTime();
        time += ( currentTime - time ) * sg_enemyCurrentTimeInfluence;
    }


    ePlayerNetID* player = cycle->Player();
    if ( !player )
        return;


    if ( thisCycle && !ePlayerNetID::Enemies( thisCycle->Player(), player ) )
    {
        return;
    }


    if ( thisCycle->Player() && player->CurrentTeam() == thisCycle->Player()->CurrentTeam() )
    {


        if ( time > cycle->GetLastTurnTime() )
            time = cycle->GetLastTurnTime();
        time -= sg_enemyFriendTimePenalty;
    }
    const ePlayerNetID* pInfluence = this->lastEnemyInfluence.GetPointer();


    REAL lastEffectiveTime = lastTime;
    if ( !pInfluence  || !pInfluence->Object() ||  !pInfluence->Object()->Alive() )
    {
        lastEffectiveTime -= sg_enemyDeadTimePenalty;
    }


    REAL effectiveTime = time;
    if ( !cycle->Alive() )
    {
        effectiveTime -= sg_enemyDeadTimePenalty;
    }


    if ( effectiveTime > lastEffectiveTime || !bool(lastEnemyInfluence) )
    {
        lastEnemyInfluence = player;
        lastTime		   = time;
    }
}
