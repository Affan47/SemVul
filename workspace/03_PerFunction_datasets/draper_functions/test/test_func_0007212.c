OGRGeocodeReverseSubstitute(CPLString osURL,
                                             double dfLon, double dfLat)
{
    size_t iPos = osURL.find("{lon}");
    if( iPos != std::string::npos )
    {
        CPLString osEnd(osURL.substr(iPos + 5));
        osURL = osURL.substr(0,iPos);
        osURL += CPLSPrintf("%.8f", dfLon);
        osURL += osEnd;
    }

    iPos = osURL.find("{lat}");
    if( iPos != std::string::npos )
    {
        CPLString osEnd(osURL.substr(iPos + 5));
        osURL = osURL.substr(0,iPos);
        osURL += CPLSPrintf("%.8f", dfLat);
        osURL += osEnd;
    }

    return osURL;
}
