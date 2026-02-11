Need_Remote_Data() const
{
  if( BTCONTENT.Seeding() || bitfield.IsEmpty() ) return 0;
  else if( bitfield.IsFull() &&
    BTCONTENT.CheckedPieces() >= BTCONTENT.GetNPieces() ) return 1;
  else{
    BitField tmpBitfield = bitfield;
    tmpBitfield.Except(*BTCONTENT.pBF);
    tmpBitfield.Except(*BTCONTENT.pBMasterFilter);
    tmpBitfield.And(*BTCONTENT.pBChecked);
    return tmpBitfield.IsEmpty() ? 0 : 1;
  }
  return 0;
}
