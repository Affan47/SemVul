resize(ushort width, ushort height, Filter filter)
    {

        assert(mAutoDelete);
        assert(mDepth == 1);


        Image temp;
        temp.loadDynamicImage(mBuffer, mWidth, mHeight, 1, mFormat, true);


        mWidth = width;
        mHeight = height;
        mBufSize = PixelUtil::getMemorySize(mWidth, mHeight, 1, mFormat);
        mBuffer = OGRE_ALLOC_T(uchar, mBufSize, MEMCATEGORY_GENERAL);
        mNumMipmaps = 0;


        Image::scale(temp.getPixelBox(), getPixelBox(), filter);
    }
