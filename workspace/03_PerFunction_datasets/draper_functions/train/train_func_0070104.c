setOption( const String & key, const void * val )
    {
        if ( key == "ShowBoundingBoxes" )
        {
            mShowBoundingBoxes = * static_cast < const bool * > ( val );
            return true;
        }

        else if ( key == "ShowPortals" )
        {
            mShowPortals = * static_cast < const bool * > ( val );
            return true;
        }

        ZoneMap::iterator i;
        PCZone * zone;
        for (i = mZones.begin(); i != mZones.end(); i++)
        {
            zone = i->second;
             if (zone->setOption(key, val ) == true)
             {
                 return true;
             }
        }


        return SceneManager::setOption( key, val );


    }
