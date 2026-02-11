Validate()

{
    if ( (size_t)eResample >=
         (sizeof(anGWKFilterRadius) / sizeof(anGWKFilterRadius[0])) )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Unsupported resampling method %d.", (int) eResample );
        return CE_Failure;
    }


    if( (eResample == GRA_CubicSpline || eResample == GRA_Lanczos) &&
         atoi(CSLFetchNameValueDef(papszWarpOptions, "EXTRA_ELTS", "0") ) != WARP_EXTRA_ELTS )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Source arrays must have WARP_EXTRA_ELTS extra elements at their end. "
                  "See GDALWarpKernel class definition. If this condition is fulfilled, "
                  "define a EXTRA_ELTS=%d warp options", WARP_EXTRA_ELTS);
        return CE_Failure;
    }

    return CE_None;
}
