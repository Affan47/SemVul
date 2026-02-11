passInMatrix(const CoinPackedMatrix & matrix)
{
  type_=3;
  packedMatrix_ = new CoinPackedMatrix(matrix);
}
