setCubicTextureName(const String* const names, bool forUVW)
    {
        setContentType(CONTENT_NAMED);
        mTextureLoadFailed = false;
        mFrames.resize(forUVW ? 1 : 6);

        mFramePtrs.resize(forUVW ? 1 : 6);
        mAnimDuration = 0;
        mCurrentFrame = 0;
        mCubic = true;
        mTextureType = forUVW ? TEX_TYPE_CUBE_MAP : TEX_TYPE_2D;

        for (unsigned int i = 0; i < mFrames.size(); ++i)
        {
            mFrames[i] = names[i];
            mFramePtrs[i].setNull();
        }

        mParent->_notifyNeedsRecompile();
    }
