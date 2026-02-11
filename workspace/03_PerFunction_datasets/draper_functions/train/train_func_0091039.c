getMicrocodeFromCache( const String & name ) const
    {
        return mMicrocodeCache.find(addRenderSystemToName(name))->second;
    }
