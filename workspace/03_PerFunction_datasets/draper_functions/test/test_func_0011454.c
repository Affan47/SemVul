DecodeBmpPacked(
  std::vector<unsigned char>& buf, unsigned int ofsData, unsigned char* dst,
  const int PITCH, const int HEIGHT, const int ROW_SIZE, const int PITCH_BUF)
{

  for (int i = 0; i < HEIGHT; ++i)
    for (int j = 0; j < ROW_SIZE; ++j)
      *(dst + (PITCH * i) + j) = buf[ofsData + (PITCH_BUF * i) + j];

}
