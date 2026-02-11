Atalasify(size_t iSizeInBytes,
                            const UINTVECTOR3& vMaxBrickSize,
                            const UINT64VECTOR3& vCurrBrickSize,
                            const UINTVECTOR2& atlasSize,
                            uint8_t* pDataSource,
                            uint8_t* pDataTarget) {


  if (pDataSource == pDataTarget) {
    uint8_t* temp = new uint8_t[iSizeInBytes];
    memcpy(temp, pDataTarget, iSizeInBytes);
    Atalasify(iSizeInBytes, vMaxBrickSize,
               vCurrBrickSize, atlasSize, temp, pDataTarget);
    delete [] temp;
    return;
  }


  const size_t iSizePerElement = size_t(iSizeInBytes/vCurrBrickSize.volume());
  const unsigned int iTilesPerRow = (unsigned int)(atlasSize.x / vMaxBrickSize.x);
  uint8_t* pDataSourceIter = pDataSource;
  for (unsigned int z = 0;z<vCurrBrickSize.z;++z) {
    const unsigned int iTileX = z % iTilesPerRow;
    const unsigned int iTileY = z / iTilesPerRow;
    for (unsigned int y = 0;y<vCurrBrickSize.y;++y) {
      memcpy(pDataTarget+(iSizePerElement*(iTileX*vMaxBrickSize.x+(iTileY*vMaxBrickSize.y+y)*atlasSize.x)),
             pDataSourceIter,
             size_t(vCurrBrickSize.x*iSizePerElement));
      pDataSourceIter += vCurrBrickSize.x*iSizePerElement;
    }
  }

}
