isZExtFree(EVT Src, EVT Dest) const {


  return Src == MVT::i32 && Dest == MVT::i64;
}
