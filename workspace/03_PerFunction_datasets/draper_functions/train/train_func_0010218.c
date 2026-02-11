imBinCPUByteOrder(void)
{
  static int CPUByteOrder = -1;

  if (CPUByteOrder == -1)
  {
	  unsigned short w = 0x0001;
	  unsigned char* b = (unsigned char*)&w;
	  CPUByteOrder = (b[0] == 0x01)? IM_LITTLEENDIAN: IM_BIGENDIAN;
  }

  return CPUByteOrder;
}
