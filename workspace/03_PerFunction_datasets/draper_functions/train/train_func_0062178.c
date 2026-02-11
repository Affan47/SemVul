isNative()
    {
        if(!KFileDialogPrivate::Native::s_allowNative)
            return false;
        KConfigGroup cfgGroup(KGlobal::config(), ConfigGroup);
        return cfgGroup.readEntry("Native", NATIVE_FILEDIALOGS_BY_DEFAULT);
    }
