GetTextCoords(BrickTable::const_iterator brick, bool bUseOnlyPowerOfTwo) const {

  if (m_bToCBlock) {
    const UINT64VECTOR4 coords = KeyToTOCVector(brick->first);
    const TOCBlock* tb = static_cast<TOCTimestep*>(m_timesteps[std::get<0>(brick->first)])->GetDB();

    uint32_t iOverlap = tb->GetOverlap();
    FLOATVECTOR3 brickAspect = FLOATVECTOR3(tb->GetBrickAspect(coords));
    FLOATVECTOR3 vTexcoordsMin;
    FLOATVECTOR3 vTexcoordsMax;

    if (bUseOnlyPowerOfTwo) {
      UINTVECTOR3 vRealVoxelCount(MathTools::NextPow2(brick->second.n_voxels.x),
        MathTools::NextPow2(brick->second.n_voxels.y),
        MathTools::NextPow2(brick->second.n_voxels.z)
        );
      vTexcoordsMin = float(iOverlap) / FLOATVECTOR3(vRealVoxelCount);
      vTexcoordsMax = 1.0f-vTexcoordsMin;
      vTexcoordsMax -= FLOATVECTOR3(vRealVoxelCount - brick->second.n_voxels) / FLOATVECTOR3(vRealVoxelCount);
    } else {
      vTexcoordsMin = float(iOverlap) / FLOATVECTOR3(brick->second.n_voxels);
      vTexcoordsMax = 1.0f-vTexcoordsMin;
    }

    return std::make_pair(vTexcoordsMin, vTexcoordsMax*brickAspect);
  } else {
    return Dataset::GetTextCoords(brick, bUseOnlyPowerOfTwo);
  }
}

}
