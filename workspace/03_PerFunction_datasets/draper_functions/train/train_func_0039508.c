World_update( World *w, f32 frame_time ) {

    for( int i = 0; i < w->agents->mCount; ++i )
        if( HandleManager_isUsed( w->agents, i ) )
            Agent_update( (Agent*)HandleManager_getData( w->agents, i ), frame_time );
}
