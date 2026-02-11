setValue(const SbVec3d & v)
{
#if COIN_DEBUG
  if (v[0] > std::numeric_limits<int32_t>::max() || v[0] < -std::numeric_limits<int32_t>::max() ||
      v[1] > std::numeric_limits<int32_t>::max() || v[1] < -std::numeric_limits<int32_t>::max() ||
      v[2] > std::numeric_limits<int32_t>::max() || v[2] < -std::numeric_limits<int32_t>::max()) {
    SoDebugError::post("SbVec3i32::setValue", "SbVec3d argument out of range for SbVec3i32");
  }
#endif
  vec[0] = static_cast<int32_t>(v[0]);
  vec[1] = static_cast<int32_t>(v[1]);
  vec[2] = static_cast<int32_t>(v[2]);
  return *this;
}
