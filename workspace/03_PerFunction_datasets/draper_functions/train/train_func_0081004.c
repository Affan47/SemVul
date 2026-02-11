setUserAny( const Any& anything )
    {

        if (mAttributes == NULL)
            mAttributes = OGRE_NEW UserObjectBindings::Attributes;

        mAttributes->mKeylessAny = anything;
    }
