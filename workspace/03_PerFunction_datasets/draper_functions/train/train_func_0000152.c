clone(const String& newName) const
    {
        Animation* newAnim = OGRE_NEW Animation(newName, mLength);
        newAnim->mInterpolationMode = mInterpolationMode;
        newAnim->mRotationInterpolationMode = mRotationInterpolationMode;


        for (NodeTrackList::const_iterator i = mNodeTrackList.begin();
            i != mNodeTrackList.end(); ++i)
        {
            i->second->_clone(newAnim);
        }
        for (NumericTrackList::const_iterator i = mNumericTrackList.begin();
            i != mNumericTrackList.end(); ++i)
        {
            i->second->_clone(newAnim);
        }
        for (VertexTrackList::const_iterator i = mVertexTrackList.begin();
            i != mVertexTrackList.end(); ++i)
        {
            i->second->_clone(newAnim);
        }

        newAnim->_keyFrameListChanged();
        return newAnim;

    }
