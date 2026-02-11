Backward( int time )
    {
        if( time > 0 && !The::engineController()->isStopped() )
            The::engineController()->seekTo( The::engineController()->trackPosition() * 1000 - time );
    }
