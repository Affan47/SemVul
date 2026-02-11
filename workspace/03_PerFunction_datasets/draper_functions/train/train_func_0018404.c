ReadObj(TABMAPObjectBlock *poObjBlock)
{
    m_nStartAngle = poObjBlock->ReadInt16();
    m_nEndAngle   = poObjBlock->ReadInt16();


    poObjBlock->ReadIntCoord(IsCompressedType(),
                             m_nArcEllipseMinX, m_nArcEllipseMinY);
    poObjBlock->ReadIntCoord(IsCompressedType(),
                             m_nArcEllipseMaxX, m_nArcEllipseMaxY);


    poObjBlock->ReadIntCoord(IsCompressedType(), m_nMinX, m_nMinY);
    poObjBlock->ReadIntCoord(IsCompressedType(), m_nMaxX, m_nMaxY);

    m_nPenId = poObjBlock->ReadByte();

    if (CPLGetLastErrorNo() != 0)
        return -1;

    return 0;
}
