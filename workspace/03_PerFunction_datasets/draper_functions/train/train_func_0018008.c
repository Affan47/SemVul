_cmsFree(cmsContext ContextID, void* Ptr)
{
    if (Ptr != NULL) {
        _cmsMemPluginChunkType* ptr = (_cmsMemPluginChunkType*) _cmsContextGetClientChunk(ContextID, MemPlugin);
        ptr ->FreePtr(ContextID, Ptr);
    }
}
