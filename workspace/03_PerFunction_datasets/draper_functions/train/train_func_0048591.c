AppendBlockToFile(std::shared_ptr<DataBlock> dataBlock) {
  if (!m_bFileIsReadWrite)  return false;


  DataBlockListElem* dble = new DataBlockListElem(dataBlock, false,
                                           m_streamFile->GetCurrentSize(),
                                           dataBlock->GetOffsetToNextBlock());
  m_DataBlocks.push_back(std::shared_ptr<DataBlockListElem>(dble));


  m_DataBlocks[m_DataBlocks.size()-2]->m_bHeaderIsDirty = true;


  dataBlock->CopyToFile(m_streamFile, m_streamFile->GetCurrentSize(),
                        m_GlobalHeader.bIsBigEndian, true);

  return true;
}
