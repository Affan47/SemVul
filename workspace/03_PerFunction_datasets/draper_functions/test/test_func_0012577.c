ensMapperAddCoordinates(EnsPMapper mapper,
                               ajuint srcoid,
                               ajint srcstart,
                               ajint srcend,
                               ajint ori,
                               ajuint trgoid,
                               ajint trgstart,
                               ajint trgend)
{
    AjBool result = AJFALSE;

    EnsPMapperpair mp = NULL;

    if (ajDebugTest("ensMapperAddCoordinates"))
        ajDebug("ensMapperAddCoordinates\n"
                "  mapper %p\n"
                "  srcoid %u\n"
                "  srcstart %d\n"
                "  srcend %d\n"
                "  ori %d\n"
                "  trgoid %u\n"
                "  trgstart %d\n"
                "  trgend %d\n",
                mapper,
                srcoid,
                srcstart,
                srcend,
                ori,
                trgoid,
                trgstart,
                trgend);

    if (!mapper)
        return ajFalse;

    if (!srcoid)
        return ajFalse;

    if (!trgoid)
        return ajFalse;

    if ((srcend - srcstart) != (trgend - trgstart))
        ajFatal("ensMapperAddCoordinates cannot deal with mis-lengthed "
                "mappings so far.\n");

    mp = ensMapperpairNewIni(srcoid, srcstart, srcend,
                             trgoid, trgstart, trgend,
                             ori, ajFalse);

    result = ensMapperAddMapperpair(mapper, mp);

    ensMapperpairDel(&mp);

    return result;
}
