SetMIFCoordSys(const char *pszMIFCoordSys)
{
    if (m_eAccessMode != TABWrite)
    {
        CPLError(CE_Failure, CPLE_NotSupported,
                 "SetMIFCoordSys() can be used only with Write access.");
        return -1;
    }


    if (m_poMAPFile && m_nLastFeatureId < 1)
    {
        OGRSpatialReference *poSpatialRef;

        poSpatialRef = MITABCoordSys2SpatialRef( pszMIFCoordSys );

        if (poSpatialRef)
        {
            double dXMin, dYMin, dXMax, dYMax;
            if (SetSpatialRef(poSpatialRef) == 0)
            {
                if (MITABExtractCoordSysBounds(pszMIFCoordSys,
                                               dXMin, dYMin,
                                               dXMax, dYMax) == TRUE)
                {

                    if (SetBounds(dXMin, dYMin, dXMax, dYMax) != 0)
                    {


                        return -1;
                    }
                }
            }
            else
            {


                return -1;
            }


            if( poSpatialRef->Dereference() == 0 )
                delete poSpatialRef;
        }
    }
    else
    {
        CPLError(CE_Failure, CPLE_AssertionFailed,
                 "SetMIFCoordSys() can be called only after dataset has been "
                 "created and before any feature is set.");
        return -1;
    }

    return 0;
}
