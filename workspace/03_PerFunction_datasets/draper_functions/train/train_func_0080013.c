CommitObjAndCoordBlocks(GBool bDeleteObjects )
{
    int nStatus = 0;


    if (m_poCurObjBlock == NULL)
        return 0;

    if (m_eAccessMode != TABWrite)
    {
        CPLError(CE_Failure, CPLE_AssertionFailed,
                 "CommitObjAndCoordBlocks() failed: file not opened for write access.");
        return -1;
    }


    if (m_poCurCoordBlock)
    {


        int nTotalCoordSize = m_poCurCoordBlock->GetNumBlocksInChain()*512;
        if (nTotalCoordSize > m_poHeader->m_nMaxCoordBufSize)
            m_poHeader->m_nMaxCoordBufSize = nTotalCoordSize;


        m_poCurObjBlock->AddCoordBlockRef(m_poCurCoordBlock->
                                                         GetStartAddress());
        nStatus = m_poCurCoordBlock->CommitToFile();

        if (bDeleteObjects)
        {
            delete m_poCurCoordBlock;
            m_poCurCoordBlock = NULL;
        }
    }


    if (nStatus == 0)
    {
        nStatus = m_poCurObjBlock->CommitToFile();
    }


    if (nStatus == 0 && m_bQuickSpatialIndexMode)
    {
        GInt32 nXMin, nYMin, nXMax, nYMax;

        if (m_poSpIndex == NULL)
        {

            m_poSpIndex = new TABMAPIndexBlock(m_eAccessMode);

            m_poSpIndex->InitNewBlock(m_fp, 512,
                                      m_oBlockManager.AllocNewBlock());
            m_poSpIndex->SetMAPBlockManagerRef(&m_oBlockManager);

            m_poHeader->m_nFirstIndexBlock = m_poSpIndex->GetNodeBlockPtr();
        }

        m_poCurObjBlock->GetMBR(nXMin, nYMin, nXMax, nYMax);
        nStatus = m_poSpIndex->AddEntry(nXMin, nYMin, nXMax, nYMax,
                                        m_poCurObjBlock->GetStartAddress());

        m_poHeader->m_nMaxSpIndexDepth = MAX(m_poHeader->m_nMaxSpIndexDepth,
                                      (GByte)m_poSpIndex->GetCurMaxDepth()+1);
    }


    if (bDeleteObjects)
    {
        delete m_poCurObjBlock;
        m_poCurObjBlock = NULL;
    }

    return nStatus;
}
