ComputeBrickSize(const UINT64VECTOR4& vBrickCoords) const {
  const VECTOR3<bool> bIsLast = IsLastBrick(vBrickCoords);
  const UINT64VECTOR3 iPixelSize = m_vLODTable[size_t(vBrickCoords.w)].m_iLODPixelSize;
  const uint32_t i2Overlap = 2*m_iOverlap;
  const UINTVECTOR3 iBrickCore = this->GetMaxBrickSize() - i2Overlap;

  return UINT64VECTOR3(bIsLast.x && (iPixelSize.x % iBrickCore.x) ? (i2Overlap + (iPixelSize.x % iBrickCore.x)) : m_iBrickSize.x,
                       bIsLast.y && (iPixelSize.y % iBrickCore.y) ? (i2Overlap + (iPixelSize.y % iBrickCore.y)) : m_iBrickSize.y,
                       bIsLast.z && (iPixelSize.z % iBrickCore.z) ? (i2Overlap + (iPixelSize.z % iBrickCore.z)) : m_iBrickSize.z);
}
