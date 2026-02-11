Distance( Sensor const & a, Sensor const & b )
    {

        if ( a.Direction() * b.Direction() < 0 )
            return Distance( b, a );

        bool self = a.type == gSENSOR_SELF || b.type == gSENSOR_SELF;
        bool rim  = a.type == gSENSOR_RIM || b.type == gSENSOR_RIM;


        REAL selfHatred = 1;
        if ( a.type == gSENSOR_SELF )
        {
            selfHatred *= .5;
            if ( a.lr > 0 )
            {
                selfHatred *= .5;
                if ( b.type == gSENSOR_RIM )
                    selfHatred *= .25;
            }
        }
        if ( b.type == gSENSOR_SELF )
        {
            selfHatred *= .5;
            if ( b.lr < 0 )
            {
                selfHatred *= .5;
                if ( a.type == gSENSOR_RIM )
                    selfHatred *= .25;
            }
        }


        REAL bigDistance = owner_->MaxWallsLength();
        if ( bigDistance <= 0 )
            bigDistance = owner_->GetDistance();

        if ( a.hitOwner_ != b.hitOwner_ )
        {

            REAL ret =
                a.hitDistance_ + b.hitDistance_;

            if ( rim )
            {
                ret = bigDistance * .001 + ret * .01 + ( a.before_hit - b.before_hit).Norm();


                if ( !self )
                    ret = bigDistance * 2;
            }


            ret *= 16;


            if ( a.type == gSENSOR_NONE || b.type == gSENSOR_NONE )
                ret *= 2;

            return ret * selfHatred;
        }
        else if ( rim )
        {

            return ( a.before_hit - b.before_hit).Norm() * selfHatred;
        }
        else if ( a.type == gSENSOR_NONE && b.type == gSENSOR_NONE )
        {

            return owner_->GetDistance() * 256;
        }
        else if ( a.lr != b.lr )
        {

            return ( fabsf( a.hitDistance_ - b.hitDistance_ ) + .25 * bigDistance ) * selfHatred;
        }


        else
        {

            return fabsf( a.hitDistance_ - b.hitDistance_ ) * selfHatred;
        }


        return ( a.before_hit - b.before_hit).Norm() * selfHatred;
    }
