getCustomAttribute(const String& name, void* pData)
    {
        if (name == "GLID")
            *static_cast<GLuint*>(pData) = mTextureID;
    }
