getNullShadowTexture(PixelFormat format)
    {
        for (ShadowTextureList::iterator t = mNullTextureList.begin(); t != mNullTextureList.end(); ++t)
        {
            const TexturePtr& tex = *t;

            if (format == tex->getFormat())
            {

                return tex;
            }
        }


        static const String baseName = "Ogre/ShadowTextureNull";
        String targName = baseName + StringConverter::toString(mCount++);
        TexturePtr shadowTex = TextureManager::getSingleton().createManual(
            targName,
            ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME,
            TEX_TYPE_2D, 1, 1, 0, format, TU_STATIC_WRITE_ONLY);
        mNullTextureList.push_back(shadowTex);


        shadowTex->getBuffer()->lock(HardwareBuffer::HBL_DISCARD);
        const PixelBox& box = shadowTex->getBuffer()->getCurrentLock();


        PixelUtil::packColour( 1.0f, 1.0f, 1.0f, 1.0f, format, box.data );

        shadowTex->getBuffer()->unlock();

        return shadowTex;

    }
