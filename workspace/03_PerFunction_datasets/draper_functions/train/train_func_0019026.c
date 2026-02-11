addCompositor(CompositorPtr filter, size_t addPosition, const String& scheme)
{


    filter->touch();
    CompositionTechnique *tech = filter->getSupportedTechnique(scheme);
    if(!tech)
    {

        LogManager::getSingleton().logMessage(
            "CompositorChain: Compositor " + filter->getName() + " has no supported techniques.", LML_CRITICAL
            );
        return 0;
    }
    CompositorInstance *t = OGRE_NEW CompositorInstance(tech, this);

    if(addPosition == LAST)
        addPosition = mInstances.size();
    else
        assert(addPosition <= mInstances.size() && "Index out of bounds.");
    mInstances.insert(mInstances.begin()+addPosition, t);

    mDirty = true;
    mAnyCompositorsEnabled = true;
    return t;
}
