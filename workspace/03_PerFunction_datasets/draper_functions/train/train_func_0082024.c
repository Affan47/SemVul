removeMovableObjectFactory(MovableObjectFactory* fact)
    {
        MovableObjectFactoryMap::iterator i = mMovableObjectFactoryMap.find(
            fact->getType());
        if (i != mMovableObjectFactoryMap.end())
        {
            mMovableObjectFactoryMap.erase(i);
        }

    }
