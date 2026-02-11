_clone(AnimationTrack* newParent) const
    {
        NumericKeyFrame* newKf = OGRE_NEW NumericKeyFrame(newParent, mTime);
        newKf->mValue = mValue;
        return newKf;
    }
