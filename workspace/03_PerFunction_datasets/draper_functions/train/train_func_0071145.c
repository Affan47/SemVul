GEOSPrepare_r(GEOSContextHandle_t extHandle, const Geometry *g)
{
    if ( 0 == extHandle )
    {
        return 0;
    }

    GEOSContextHandleInternal_t *handle = 0;
    handle = reinterpret_cast<GEOSContextHandleInternal_t*>(extHandle);
    if ( 0 == handle->initialized )
    {
        return 0;
    }

    const geos::geom::prep::PreparedGeometry* prep = 0;

    try
    {
        prep = geos::geom::prep::PreparedGeometryFactory::prepare(g);
    }
    catch (const std::exception &e)
    {
        handle->ERROR_MESSAGE("%s", e.what());
    }
    catch (...)
    {
        handle->ERROR_MESSAGE("Unknown exception thrown");
    }

    return prep;
}
