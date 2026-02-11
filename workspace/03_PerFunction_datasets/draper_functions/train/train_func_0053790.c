GEOSisValid_r(GEOSContextHandle_t extHandle, const Geometry *g1)
{
    if ( 0 == extHandle )
    {
        return 2;
    }

    GEOSContextHandleInternal_t *handle = 0;
    handle = reinterpret_cast<GEOSContextHandleInternal_t*>(extHandle);
    if ( 0 == handle->initialized )
    {
        return 2;
    }

    try
    {
        using geos::operation::valid::IsValidOp;
        using geos::operation::valid::TopologyValidationError;

        IsValidOp ivo(g1);
        TopologyValidationError *err = ivo.getValidationError();
        if ( err )
        {
           handle->NOTICE_MESSAGE("%s", err->toString().c_str());
           return 0;
        }
        else
        {
           return 1;
        }
    }
    catch (const std::exception &e)
    {
        handle->ERROR_MESSAGE("%s", e.what());
    }
    catch (...)
    {
        handle->ERROR_MESSAGE("Unknown exception thrown");
    }

    return 2;
}
