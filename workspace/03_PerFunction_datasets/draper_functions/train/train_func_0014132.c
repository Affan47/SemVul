createUnit(bool ignRedefs, bool all, bool allowIcePrefix, bool caseSensitive,
                        const StringList& defaultGlobalMetadata)
{
    return new Unit(ignRedefs, all, allowIcePrefix, caseSensitive, defaultGlobalMetadata);
}
