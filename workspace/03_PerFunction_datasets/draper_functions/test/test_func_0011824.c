ReadNextFeature( OGRFeatureDefn * poTarget )

{
    if( !bFileIngested && !Ingest() )
        return NULL;


    if( poMultiPoint != NULL )
    {
        if( poTarget == NULL || poTarget == poMultiPoint->GetDefnRef() )
        {
            return NextPendingMultiPoint();
        }
        else
        {
            ClearPendingMultiPoint();
        }
    }


    if( (nOptionFlags & S57M_RETURN_DSID)
        && nNextDSIDIndex == 0
        && (poTarget == NULL || EQUAL(poTarget->GetName(),"DSID")) )
    {
        return ReadDSID();
    }


    if( nOptionFlags & S57M_RETURN_PRIMITIVES )
    {
        int nRCNM = 0;
        int *pnCounter = NULL;

        if( poTarget == NULL )
        {
            if( nNextVIIndex < oVI_Index.GetCount() )
            {
                nRCNM = RCNM_VI;
                pnCounter = &nNextVIIndex;
            }
            else if( nNextVCIndex < oVC_Index.GetCount() )
            {
                nRCNM = RCNM_VC;
                pnCounter = &nNextVCIndex;
            }
            else if( nNextVEIndex < oVE_Index.GetCount() )
            {
                nRCNM = RCNM_VE;
                pnCounter = &nNextVEIndex;
            }
            else if( nNextVFIndex < oVF_Index.GetCount() )
            {
                nRCNM = RCNM_VF;
                pnCounter = &nNextVFIndex;
            }
        }
        else
        {
            if( EQUAL(poTarget->GetName(),OGRN_VI) )
            {
                nRCNM = RCNM_VI;
                pnCounter = &nNextVIIndex;
            }
            else if( EQUAL(poTarget->GetName(),OGRN_VC) )
            {
                nRCNM = RCNM_VC;
                pnCounter = &nNextVCIndex;
            }
            else if( EQUAL(poTarget->GetName(),OGRN_VE) )
            {
                nRCNM = RCNM_VE;
                pnCounter = &nNextVEIndex;
            }
            else if( EQUAL(poTarget->GetName(),OGRN_VF) )
            {
                nRCNM = RCNM_VF;
                pnCounter = &nNextVFIndex;
            }
        }

        if( nRCNM != 0 )
        {
            OGRFeature *poFeature = ReadVector( *pnCounter, nRCNM );
            if( poFeature != NULL )
            {
                *pnCounter += 1;
                return poFeature;
            }
        }
    }


    while( nNextFEIndex < oFE_Index.GetCount() )
    {
        OGRFeature      *poFeature;
        OGRFeatureDefn *poFeatureDefn;

        poFeatureDefn = (OGRFeatureDefn *)
            oFE_Index.GetClientInfoByIndex( nNextFEIndex );

        if( poFeatureDefn == NULL )
        {
            poFeatureDefn = FindFDefn( oFE_Index.GetByIndex( nNextFEIndex ) );
            oFE_Index.SetClientInfoByIndex( nNextFEIndex, poFeatureDefn );
        }

        if( poFeatureDefn != poTarget && poTarget != NULL )
        {
            nNextFEIndex++;
            continue;
        }

        poFeature = ReadFeature( nNextFEIndex++, poTarget );
        if( poFeature != NULL )
        {
            if( (nOptionFlags & S57M_SPLIT_MULTIPOINT)
                && poFeature->GetGeometryRef() != NULL
                && wkbFlatten(poFeature->GetGeometryRef()->getGeometryType())
                                                        == wkbMultiPoint)
            {
                poMultiPoint = poFeature;
                iPointOffset = 0;
                return NextPendingMultiPoint();
            }

            return poFeature;
        }
    }

    return NULL;
}
