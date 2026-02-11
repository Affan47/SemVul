GetColorInterpretation()

{
    if( poGDS->eGDALColorSpace == JCS_GRAYSCALE )
        return GCI_GrayIndex;

    else if( poGDS->eGDALColorSpace == JCS_RGB)
    {
        if ( nBand == 1 )
            return GCI_RedBand;

        else if( nBand == 2 )
            return GCI_GreenBand;

        else
            return GCI_BlueBand;
    }
    else if( poGDS->eGDALColorSpace == JCS_CMYK)
    {
        if ( nBand == 1 )
            return GCI_CyanBand;

        else if( nBand == 2 )
            return GCI_MagentaBand;

        else if ( nBand == 3 )
            return GCI_YellowBand;

        else
            return GCI_BlackBand;
    }
    else if( poGDS->eGDALColorSpace == JCS_YCbCr ||
             poGDS->eGDALColorSpace == JCS_YCCK)
    {
        if ( nBand == 1 )
            return GCI_YCbCr_YBand;

        else if( nBand == 2 )
            return GCI_YCbCr_CbBand;

        else if ( nBand == 3 )
            return GCI_YCbCr_CrBand;

        else
            return GCI_BlackBand;
    }
    else
    {
        CPLAssert(0);
        return GCI_Undefined;
    }
}
