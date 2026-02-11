IsValidRequest(size_t idx,size_t off,size_t len) const
{
  return ( idx < BTCONTENT.GetNPieces() &&
           len &&
           (off + len) <= BTCONTENT.GetPieceLength(idx) &&
           len <= cfg_max_slice_size ) ?
    1 : 0;
}
