setValue(const SbVec2i32 & v)
{
#if COIN_DEBUG
  if (v[0] > std::numeric_limits<int8_t>::max() || v[0] < -std::numeric_limits<int8_t>::max() ||
      v[1] > std::numeric_limits<int8_t>::max() || v[1] < -std::numeric_limits<int8_t>::max()) {
    SoDebugError::post("SbVec2b::setValue", "SbVec2i32 argument out of range for SbVec2b");
  }
#endif
  vec[0] = static_cast<int8_t>(v[0]);
  vec[1] = static_cast<int8_t>(v[1]);
  return *this;
}
