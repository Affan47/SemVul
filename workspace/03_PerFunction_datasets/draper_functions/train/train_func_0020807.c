GEOSPreparedGeom_destroy_r(GEOSContextHandle_t extHandle, const geos::geom::prep::PreparedGeometry *a)
{
    GEOSContextHandleInternal_t *handle = 0;

    try
    {
        delete a;
    }
    catch (const std::exception &e)
    {
        if ( 0 == extHandle )
        {
            return;
        }

        handle = reinterpret_cast<GEOSContextHandleInternal_t*>(extHandle);
        if ( 0 == handle->initialized )
        {
            return;
        }

        handle->ERROR_MESSAGE("%s", e.what());
    }
    catch (...)
    {
        if ( 0 == extHandle )
        {
            return;
        }

        handle = reinterpret_cast<GEOSContextHandleInternal_t*>(extHandle);
        if ( 0 == handle->initialized )
        {
            return;
        }

        handle->ERROR_MESSAGE("Unknown exception thrown");
    }
}
