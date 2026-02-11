addCustomScriptTranslator(const String& key, ScriptTranslator* translator)
{
    OGRE_LOCK_AUTO_MUTEX;

    SGScriptTranslatorIterator itFind = mScriptTranslatorsMap.find(key);

    if (itFind != mScriptTranslatorsMap.end())
        return false;

    mScriptTranslatorsMap[key] = translator;

    return true;
}
