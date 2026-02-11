GetMaxUsedBrickSizes() const
{
  UINT64VECTOR3 vMaxSize(1,1,1);
  UINT64VECTOR3 vAbsoluteMax(m_aMaxBrickSize);
  if (m_bToCBlock) {
    for(size_t tsi=0; tsi < m_timesteps.size(); ++tsi) {
      const TOCTimestep* ts = (TOCTimestep*)m_timesteps[tsi];


      vMaxSize.StoreMax(UINT64VECTOR3(ts->GetDB()->GetBrickSize(UINT64VECTOR4(0,0,0,0))));

      if (vMaxSize == vAbsoluteMax) return vAbsoluteMax;
    }
    return vMaxSize;
  } else {
    UINT64VECTOR3 vAbsoluteMax(m_aMaxBrickSize);

    for(size_t tsi=0; tsi < m_timesteps.size(); ++tsi) {
      const RDTimestep* ts = (RDTimestep*)m_timesteps[tsi];

      for (size_t iLOD=0;iLOD < ts->m_vvaBrickSize.size(); iLOD++) {
        for (size_t iX=0; iX < ts->m_vvaBrickSize[iLOD].size(); iX++) {
          for (size_t iY=0; iY < ts->m_vvaBrickSize[iLOD][iX].size(); iY++) {
            for (size_t iZ=0; iZ < ts->m_vvaBrickSize[iLOD][iX][iY].size(); iZ++) {
              vMaxSize.StoreMax(ts->m_vvaBrickSize[iLOD][iX][iY][iZ]);


              if (vMaxSize == vAbsoluteMax) return vAbsoluteMax;
            }
          }
        }
      }
    }

    return vMaxSize;
  }

}
