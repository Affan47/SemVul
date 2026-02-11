setValue(const SbVec4d & v)
{
#if COIN_DEBUG
  if (v[0] > std::numeric_limits<float>::max() || v[0] < -std::numeric_limits<float>::max() ||
      v[1] > std::numeric_limits<float>::max() || v[1] < -std::numeric_limits<float>::max() ||
      v[2] > std::numeric_limits<float>::max() || v[2] < -std::numeric_limits<float>::max()) {
    SoDebugError::post("SbVec4f::setValue", "SbVec4d argument out of range for SbVec4f storage");
  }
#endif
  vec[0] = static_cast<float>(v[0]);
  vec[1] = static_cast<float>(v[1]);
  vec[2] = static_cast<float>(v[2]);
  vec[3] = static_cast<float>(v[3]);
  return *this;
}
