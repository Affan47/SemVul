decode(const ByteVector &data)
{
  ByteVector result = data;

  ByteVector pattern(2, char(0));
  pattern[0] = '\xFF';
  pattern[1] = '\x00';

  return result.replace(pattern, '\xFF');
}
