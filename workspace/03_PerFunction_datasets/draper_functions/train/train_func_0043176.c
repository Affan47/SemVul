removeAnimationState(const String& name)
    {
            OGRE_LOCK_AUTO_MUTEX;

        AnimationStateMap::iterator i = mAnimationStates.find(name);
        if (i != mAnimationStates.end())
        {
            mEnabledAnimationStates.remove(i->second);

            OGRE_DELETE i->second;
            mAnimationStates.erase(i);
        }
    }
