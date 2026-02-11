GEOSWKBWriter_create_r(GEOSContextHandle_t extHandle)
{
    if ( 0 == extHandle )
    {
        return NULL;
    }

    GEOSContextHandleInternal_t *handle = 0;
    handle = reinterpret_cast<GEOSContextHandleInternal_t*>(extHandle);
    if ( 0 == handle->initialized )
    {
        return NULL;
    }

    try
    {
        using geos::io::WKBWriter;
        return new WKBWriter();
    }
    catch (const std::exception &e)
    {
        handle->ERROR_MESSAGE("%s", e.what());
    }
    catch (...)
    {
        handle->ERROR_MESSAGE("Unknown exception thrown");
    }

    return NULL;
}
