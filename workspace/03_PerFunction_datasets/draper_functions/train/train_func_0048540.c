checkExtension(const String& ext) const
    {
        assert(!extensionList.empty() && "ExtensionList is empty!" );

        return extensionList.find(ext) != extensionList.end() || mNative->checkExtension(ext);
    }
