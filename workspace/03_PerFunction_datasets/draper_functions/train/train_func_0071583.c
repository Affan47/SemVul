createOrRetrieve(
            const String &name, const String& group, bool isManual, ManualResourceLoader* loader,
            const NameValuePairList* createParams, TextureType texType, int numMipmaps, Real gamma,
            bool isAlpha, PixelFormat desiredFormat, bool hwGamma)
    {
        ResourceCreateOrRetrieveResult res =
            Ogre::ResourceManager::createOrRetrieve(name, group, isManual, loader, createParams);

        if(res.second)
        {
            TexturePtr tex = res.first.staticCast<Texture>();
            tex->setTextureType(texType);
            tex->setNumMipmaps((numMipmaps == MIP_DEFAULT)? mDefaultNumMipmaps :
                static_cast<size_t>(numMipmaps));
            tex->setGamma(gamma);
            tex->setTreatLuminanceAsAlpha(isAlpha);
            tex->setFormat(desiredFormat);
            tex->setHardwareGammaEnabled(hwGamma);
        }
        return res;
    }
