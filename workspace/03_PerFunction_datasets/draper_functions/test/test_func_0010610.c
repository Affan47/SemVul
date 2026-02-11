execute(SceneQueryListener* listener)
    {
        PCZSceneNodeList list;

        static_cast<PCZSceneManager*>( mParentSceneMgr ) -> findNodesIn( mSphere, list, mStartZone, (PCZSceneNode*)mExcludeNode );


        PCZSceneNodeList::iterator it = list.begin();
        while( it != list.end() )
        {
            SceneNode::ObjectIterator oit = (*it) -> getAttachedObjectIterator();
            while( oit.hasMoreElements() )
            {
                MovableObject * m = oit.getNext();
                if( (m->getQueryFlags() & mQueryMask) &&
                    (m->getTypeFlags() & mQueryTypeMask) &&
                    m->isInScene() &&
                    mSphere.intersects( m->getWorldBoundingBox() ) )
                {
                    listener -> queryResult( m );

                    if (m->getMovableType() == "Entity")
                    {
                        Entity* e = static_cast<Entity*>(m);
                        Entity::ChildObjectListIterator childIt = e->getAttachedObjectIterator();
                        while(childIt.hasMoreElements())
                        {
                            MovableObject* c = childIt.getNext();
                            if (c->getQueryFlags() & mQueryMask &&
                                mSphere.intersects( c->getWorldBoundingBox()))
                            {
                                listener->queryResult(c);
                            }
                        }
                    }
                }
            }
            ++it;
        }

        mStartZone = 0;
        mExcludeNode = 0;
    }
