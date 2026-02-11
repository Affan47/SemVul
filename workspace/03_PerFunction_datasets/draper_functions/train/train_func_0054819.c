IsEmpty() const
{
  return ( bitfield.IsEmpty() && TotalUL() < BTCONTENT.GetPieceLength()*2 ) ?
    1:0;
}
