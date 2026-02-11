ComputeLODLevelSizeAndOffsetTables(const vector<uint64_t>& vReducedDomainSize, uint64_t iLOD) {
  uint64_t ulSize = 0;


  uint64_t uiBitsPerElement = ComputeElementSize();


  vector<vector<uint64_t>> vBricks = ComputeBricks(vReducedDomainSize);
  vector<vector<uint64_t>> vBrickPermutation = GenerateCartesianProduct(vBricks);

  for (size_t i=0; i < vBricks.size(); i++) {
    m_vBrickCount[size_t(iLOD)].push_back(vBricks[i].size());
  }
  m_vBrickOffsets[size_t(iLOD)].push_back(0);
  m_vBrickSizes[size_t(iLOD)] = vBrickPermutation;

  ulSize = 0;
  for (size_t i = 0;i<vBrickPermutation.size();i++) {
    uint64_t ulBrickSize = vBrickPermutation[i][0];
    for (size_t j = 1;j<vBrickPermutation[i].size();j++) {
      ulBrickSize *= vBrickPermutation[i][j];
    }
    ulSize += ulBrickSize;

    if (i<vBrickPermutation.size()-1) m_vBrickOffsets[size_t(iLOD)].push_back(ulSize*uiBitsPerElement);
  }

  return  ulSize * uiBitsPerElement;
}
