operator==(const Range& range) const
{
  return startByte == range.startByte &&
    endByte == range.endByte &&
    entityLength == range.entityLength;
}
