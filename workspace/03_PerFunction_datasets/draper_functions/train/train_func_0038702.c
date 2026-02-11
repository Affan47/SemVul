loadRawData(const String &name, const String& group,
        DataStreamPtr& stream, ushort uWidth, ushort uHeight,
        PixelFormat format, TextureType texType,
        int numMipmaps, Real gamma, bool hwGamma)
    {
        TexturePtr tex = createResource(name, group, true).staticCast<Texture>();

        tex->setTextureType(texType);
        tex->setNumMipmaps((numMipmaps == MIP_DEFAULT)? mDefaultNumMipmaps :
            static_cast<size_t>(numMipmaps));
        tex->setGamma(gamma);
        tex->setHardwareGammaEnabled(hwGamma);
        tex->loadRawData(stream, uWidth, uHeight, format);

        return tex;
    }
