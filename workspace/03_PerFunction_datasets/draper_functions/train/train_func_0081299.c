setAnimatedTextureName( const String& name, unsigned int numFrames, Real duration)
    {
        setContentType(CONTENT_NAMED);
        mTextureLoadFailed = false;

        String ext;
        String baseName;

        size_t pos = name.find_last_of(".");
        baseName = name.substr(0, pos);
        ext = name.substr(pos);

        mFrames.resize(numFrames);

        mFramePtrs.resize(numFrames);
        mAnimDuration = duration;
        mCurrentFrame = 0;
        mCubic = false;

        for (unsigned int i = 0; i < mFrames.size(); ++i)
        {
            StringStream str;
            str << baseName << "_" << i << ext;
            mFrames[i] = str.str();
            mFramePtrs[i].setNull();
        }


        if (isLoaded())
        {
            _load();
        }

        if( Pass::getHashFunction() == Pass::getBuiltinHashFunction( Pass::MIN_TEXTURE_CHANGE ) )
        {
            mParent->_dirtyHash();
        }

    }
