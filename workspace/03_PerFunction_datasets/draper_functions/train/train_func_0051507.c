FindHugReplacement( Sensor const & sensor )
    {
        gCycle const * owner = sensor.hitOwner_;
        if (!owner)
            return;


        if ( !hugReplacement_.owner_ && sensor.type != gSENSOR_SELF &&
                owner != hugLeft_.owner_ &&
                owner != hugRight_.owner_ )
        {
            hugReplacement_.owner_ = sensor.hitOwner_;
            hugReplacement_.lastTimeSeen_ = nextChatAI_;
        }


        if ( owner == hugLeft_.owner_ )
            hugLeft_.lastTimeSeen_ = nextChatAI_;
        if ( owner == hugRight_.owner_ )
            hugRight_.lastTimeSeen_ = nextChatAI_;
    }
