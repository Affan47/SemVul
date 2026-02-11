orderMatrix()
{
  for (int i=0;i<majorDim_;i++) {
    CoinBigIndex start = start_[i];
    CoinBigIndex end = start + length_[i];
    CoinSort_2(index_+start,index_+end,element_+start);
  }
}
