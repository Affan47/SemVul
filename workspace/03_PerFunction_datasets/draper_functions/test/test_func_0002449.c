SetCurveDataDescriptor(const uint16_t * values, size_t num)
{
  Internal->CurveDataDescriptor = std::vector<uint16_t>(values, values+num);
}
