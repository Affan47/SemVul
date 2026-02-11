MKBlockChecksum(uint32_t* ckSum, const unsigned char* data, size_t len) {
  uint32_t* curDWordPtr;
  uint32_t curDWord;
  uint32_t myCkSum;

  myCkSum = *ckSum;

  if(data) {
    curDWordPtr = (uint32_t*) data;
    while(curDWordPtr < (uint32_t*)(&data[len & 0xFFFFFFFC])) {
      curDWord = *curDWordPtr;
      FLIPENDIAN(curDWord);
      myCkSum = curDWord + ((myCkSum >> 31) | (myCkSum << 1));
      curDWordPtr++;
    }
  }

  *ckSum = myCkSum;
  return myCkSum;
}
