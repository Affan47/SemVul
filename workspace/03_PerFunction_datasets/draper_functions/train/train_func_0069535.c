ensCacheTrace(const EnsPCache cache, ajuint level)
{
    double ratio = 0.0;

    AjPStr indent = NULL;

    if (!cache)
        return ajFalse;

    indent = ajStrNew();

    ajStrAppendCountK(&indent, ' ', level * 2);

    if (cache->Hit || cache->Miss)
        ratio = (double) cache->Hit /
            ((double) cache->Hit + (double) cache->Miss);

    ajDebug("%SensCache trace %p\n"
            "%S  Label '%S'\n"
            "%S  List %p length: %Lu\n"
            "%S  Table %p length: %Lu\n"
            "%S  Type %d\n"
            "%S  Synchron '%B'\n"
            "%S  MaxBytes %Lu\n"
            "%S  MaxCount %u\n"
            "%S  MaxSize %Lu\n"
            "%S  Bytes %Lu\n"
            "%S  Count %u\n"
            "%S  Dropped %u\n"
            "%S  Removed %u\n"
            "%S  Stored %u\n"
            "%S  Hit %u\n"
            "%S  Miss %u\n"
            "%S  Hit/(Hit + Miss) %f\n",
            indent, cache,
            indent, cache->Label,
            indent, cache->List, ajListGetLength(cache->List),
            indent, cache->Table, ajTableGetLength(cache->Table),
            indent, cache->Type,
            indent, cache->Synchron,
            indent, cache->MaxBytes,
            indent, cache->MaxCount,
            indent, cache->MaxSize,
            indent, cache->Bytes,
            indent, cache->Count,
            indent, cache->Dropped,
            indent, cache->Removed,
            indent, cache->Stored,
            indent, cache->Hit,
            indent, cache->Miss,
            indent, ratio);

    ajStrDel(&indent);

    return ajTrue;
}
