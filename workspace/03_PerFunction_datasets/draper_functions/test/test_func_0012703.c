copyDetailsTo(MaterialPtr& mat) const
    {

        ResourceHandle savedHandle = mat->mHandle;
        String savedName = mat->mName;
        String savedGroup = mat->mGroup;
        ManualResourceLoader* savedLoader = mat->mLoader;
        bool savedManual = mat->mIsManual;

        *mat = *this;

        mat->mName = savedName;
        mat->mHandle = savedHandle;
        mat->mGroup = savedGroup;
        mat->mIsManual = savedManual;
        mat->mLoader = savedLoader;

    }
