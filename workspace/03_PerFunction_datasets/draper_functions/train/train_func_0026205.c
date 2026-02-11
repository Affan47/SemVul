GetData(std::vector<double>& vData,
                              const std::vector<uint64_t>& vLOD,
                              const std::vector<uint64_t>& vBrick) const
{
  if(!ValidBrickIndex(vLOD, vBrick)) { return false; }
  const size_t bytes = GetBrickByteSize(vLOD, vBrick);
  size_vector_for_io(vData, bytes);
  return GetData(reinterpret_cast<uint8_t*>(&vData[0]), bytes, vLOD, vBrick);
}
