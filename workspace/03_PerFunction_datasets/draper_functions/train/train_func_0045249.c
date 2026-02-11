GEOSGetCentroid_r(GEOSContextHandle_t extHandle, const Geometry *g)
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
        Geometry *ret = g->getCentroid();
        if (0 == ret)
        {
            const GeometryFactory *gf = handle->geomFactory;
            return gf->createPoint();
        }
        return ret;
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
