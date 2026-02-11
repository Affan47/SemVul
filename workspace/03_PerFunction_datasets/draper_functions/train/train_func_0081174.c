dirtyNodeByMovingPortals(void)
    {


        for ( PortalList::iterator it = mPortals.begin(); it != mPortals.end(); ++it )
        {
            if ((*it)->needUpdate())
            {

                PCZSceneNodeList::iterator it2 = mHomeNodeList.begin();
                while ( it2 != mHomeNodeList.end() )
                {
                    (*it2)->setMoved(true);
                    ++it2;
                }


                it2 = mVisitorNodeList.begin();
                while ( it2 != mVisitorNodeList.end() )
                {
                    (*it2)->setMoved(true);
                    ++it2;
                }
                return;
            }
        }
    }
