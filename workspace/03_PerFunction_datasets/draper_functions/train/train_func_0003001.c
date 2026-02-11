sg_TopologyPoliceCheck( gCycle* cycle, eWall* oldWall, gPlayerWall* newWall, const eCoord& point, bool split )
{

    if ( !sg_topologyPolice && !sg_gnuplotDebug )
        return;


    REAL oldAlpha = oldWall->Edge()->Ratio( point );
    REAL newAlpha = newWall->Edge()->Ratio( point );
    clamp01( newAlpha );
    clamp01( oldAlpha );


    REAL time = newWall->Time( newAlpha );


    if ( !newWall->IsDangerous( newAlpha, se_GameTime() ) )
        return;


    gPlayerWall* oldPlayerWall = dynamic_cast< gPlayerWall* >( oldWall );
    if ( oldPlayerWall && !oldPlayerWall->IsDangerous( oldAlpha, se_GameTime() ) )
        return;


#ifdef DEBUG
    if ( sg_gnuplotDebug )
    {
        std::stringstream filename;
        if ( cycle && cycle->Player() )
        {
            filename << cycle->Player()->GetUserName() << "_";
        }
        filename << "topology";
        std::ofstream f( filename.str().c_str(), std::ios::app );
        f << point.x << " " << point.y << "\n";
    }
#endif


    if ( !sg_topologyPolice || ( !split && !sg_topologyPoliceParallel ) )
        return;

    gTopologyPoliceConsoleFiler filter;


    try
    {
        cycle->PassEdge( oldWall, time, oldAlpha );
    }
    catch ( gCycleDeath const & death )
    {
        cycle->KillAt( death.pos_ );
    }
}
