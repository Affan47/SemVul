BuildLineStrings()
{
    int i, iter;

    for(iter=0;iter<(int)listFEA_PAR.size();iter++)
    {
        const CPLString& osFEA = listFEA_PAR[iter].first;
        const strListType & aosPAR = listFEA_PAR[iter].second;
        OGRFeature* poFeature = CreateFeature(osFEA);
        if (poFeature)
        {
            OGRMultiLineString* poMulti = NULL;
            for(int k=0;k<(int)aosPAR.size();k++)
            {
                const std::map< CPLString, xyPairListType >::iterator itPAR =
                                                    mapPAR.find(aosPAR[k]);
                if (itPAR != mapPAR.end())
                {
                    const xyPairListType& arc = itPAR->second;

                    OGRLineString* poLS = new OGRLineString();
                    poLS->setNumPoints((int)arc.size());
                    for(i=0;i<(int)arc.size();i++)
                    {
                        poLS->setPoint(i, arc[i].first, arc[i].second);
                    }

                    if (poFeature->GetGeometryRef() != NULL)
                    {
                        if (poMulti == NULL)
                        {
                            OGRLineString* poPrevLS =
                                (OGRLineString*) poFeature->StealGeometry();
                            poMulti = new OGRMultiLineString();
                            poMulti->addGeometryDirectly(poPrevLS);
                            poFeature->SetGeometryDirectly(poMulti);
                        }
                        poMulti->addGeometryDirectly(poLS);
                    }
                    else
                        poFeature->SetGeometryDirectly(poLS);
                }
                else
                    CPLDebug("EDIGEO",
                             "ERROR: Cannot find ARC %s", aosPAR[k].c_str());
            }
            if (poFeature->GetGeometryRef())
                poFeature->GetGeometryRef()->assignSpatialReference(poSRS);
        }
    }

    return TRUE;
}
