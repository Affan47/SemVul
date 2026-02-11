CreateMaskBand( int nFlags )
{
    if (poMaskBand != NULL)
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "This VRT dataset has already a mask band");
        return CE_Failure;
    }

    SetMaskBand(new VRTSourcedRasterBand( this, 0 ));

    return CE_None;
}
