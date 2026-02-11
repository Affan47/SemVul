BuildLayerDefn(OGRFeatureDefn* poSrcFDefn)
{
    int bUnsetWidthPrecision = FALSE;

    poFeatureDefn = new OGRFeatureDefn( pszName );
    poFeatureDefn->Reference();

    OGRDataSource* poDS = NULL;

    if (poSrcFDefn == NULL)
        poSrcFDefn = DescribeFeatureType();
    if (poSrcFDefn == NULL)
    {
        poDS = FetchGetFeature(1);
        if (poDS == NULL)
        {
            return poFeatureDefn;
        }
        poSrcFDefn = poDS->GetLayer(0)->GetLayerDefn();
        bGotApproximateLayerDefn = TRUE;

        bUnsetWidthPrecision = TRUE;
    }

    CPLString osPropertyName = CPLURLGetValue(pszBaseURL, "PROPERTYNAME");
    const char* pszPropertyName = osPropertyName.c_str();

    int i;
    poFeatureDefn->SetGeomType(poSrcFDefn->GetGeomType());
    for(i=0;i<poSrcFDefn->GetFieldCount();i++)
    {
        if (pszPropertyName[0] != 0)
        {
            if (strstr(pszPropertyName,
                       poSrcFDefn->GetFieldDefn(i)->GetNameRef()) != NULL)
                poFeatureDefn->AddFieldDefn(poSrcFDefn->GetFieldDefn(i));
            else
                bGotApproximateLayerDefn = TRUE;
        }
        else
        {
            OGRFieldDefn oFieldDefn(poSrcFDefn->GetFieldDefn(i));
            if (bUnsetWidthPrecision)
            {
                oFieldDefn.SetWidth(0);
                oFieldDefn.SetPrecision(0);
            }
            poFeatureDefn->AddFieldDefn(&oFieldDefn);
        }
    }

    if (poDS)
        OGRDataSource::DestroyDataSource(poDS);
    else
        delete poSrcFDefn;

    return poFeatureDefn;
}
