ReadGeometryFromMAPFile(TABMAPFile *poMapFile,
                                           TABMAPObjHdr *poObjHdr,
                                           GBool bCoordBlockDataOnly ,
                                           TABMAPCoordBlock **ppoCoordBlock)
{
    GInt32              nX, nY;
    double              dX, dY, dXMin, dYMin, dXMax, dYMax;
    OGRGeometry         *poGeometry=NULL;
    GBool               bComprCoord = poObjHdr->IsCompressedType();
    TABMAPCoordBlock    *poCoordBlock = NULL;


    m_nMapInfoType = poObjHdr->m_nType;


    if (m_nMapInfoType == TAB_GEOM_MULTIPOINT ||
        m_nMapInfoType == TAB_GEOM_MULTIPOINT_C ||
        m_nMapInfoType == TAB_GEOM_V800_MULTIPOINT ||
        m_nMapInfoType == TAB_GEOM_V800_MULTIPOINT_C )
    {


        TABMAPObjMultiPoint *poMPointHdr = (TABMAPObjMultiPoint *)poObjHdr;


        poMapFile->Int2Coordsys(poMPointHdr->m_nMinX, poMPointHdr->m_nMinY,
                                dXMin, dYMin);
        poMapFile->Int2Coordsys(poMPointHdr->m_nMaxX, poMPointHdr->m_nMaxY,
                                dXMax, dYMax);

        if (!bCoordBlockDataOnly)
        {
            m_nSymbolDefIndex = poMPointHdr->m_nSymbolId;
            poMapFile->ReadSymbolDef(m_nSymbolDefIndex, &m_sSymbolDef);
        }


        poMapFile->Int2Coordsys(poMPointHdr->m_nLabelX, poMPointHdr->m_nLabelY,
                                dX, dY);
        SetCenter(dX, dY);


        m_nComprOrgX = poMPointHdr->m_nComprOrgX;
        m_nComprOrgY = poMPointHdr->m_nComprOrgY;


        OGRMultiPoint   *poMultiPoint;
        poGeometry = poMultiPoint = new OGRMultiPoint();

        if (ppoCoordBlock != NULL && *ppoCoordBlock != NULL)
            poCoordBlock = *ppoCoordBlock;
        else
            poCoordBlock = poMapFile->GetCoordBlock(poMPointHdr->m_nCoordBlockPtr);
        poCoordBlock->SetComprCoordOrigin(m_nComprOrgX,
                                          m_nComprOrgY);

        for(int iPoint=0; iPoint<poMPointHdr->m_nNumPoints; iPoint++)
        {
            if (poCoordBlock->ReadIntCoord(bComprCoord, nX, nY) != 0)
            {
                CPLError(CE_Failure, CPLE_FileIO,
                         "Failed reading coordinate data at offset %d",
                         poMPointHdr->m_nCoordBlockPtr);
                return -1;
            }

            poMapFile->Int2Coordsys(nX, nY, dX, dY);
            OGRPoint *poPoint = new OGRPoint(dX, dY);

            if (poMultiPoint->addGeometryDirectly(poPoint) != OGRERR_NONE)
            {
                CPLAssert(FALSE);
            }
        }

    }
    else
    {
        CPLError(CE_Failure, CPLE_AssertionFailed,
           "ReadGeometryFromMAPFile(): unsupported geometry type %d (0x%2.2x)",
                 m_nMapInfoType, m_nMapInfoType);
        return -1;
    }

    SetGeometryDirectly(poGeometry);

    SetMBR(dXMin, dYMin, dXMax, dYMax);


    SetIntMBR(poObjHdr->m_nMinX, poObjHdr->m_nMinY,
              poObjHdr->m_nMaxX, poObjHdr->m_nMaxY);


    if (ppoCoordBlock)
        *ppoCoordBlock = poCoordBlock;

    return 0;
}
