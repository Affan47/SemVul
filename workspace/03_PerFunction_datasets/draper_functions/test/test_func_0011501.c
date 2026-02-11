getOptimalMemOpType(uint64_t Size, unsigned DstAlign,
                                          unsigned SrcAlign, bool IsMemset,
                                          bool ZeroMemset,
                                          bool MemcpyStrSrc,
                                          MachineFunction &MF) const {


  if (Size >= 16 && DstAlign >= 4)
    return MVT::v4i32;

  if (Size >= 8 && DstAlign >= 4)
    return MVT::v2i32;


  return MVT::Other;
}
