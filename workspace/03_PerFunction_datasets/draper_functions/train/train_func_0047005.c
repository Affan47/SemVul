WriteSlice(unsigned char* pData,
                               const TransferFunction1D* pTrans,
                               uint64_t iBitWidth,
                               const std::string& strCurrentDiFilename,
                               const UINT64VECTOR2& vSize,
                               float fRescale,
                               uint64_t iComponentCount) {
    size_t iImageCompCount = (iComponentCount == 3 || iComponentCount == 2) ? 3 : 4;

    using namespace boost;
    switch (iComponentCount)  {
      case 1 : switch (iBitWidth)  {
                case 8 : ApplyTFInplace(pData, vSize, fRescale, pTrans); break;
                case 16 : ApplyTFInplace(reinterpret_cast<uint16_t*>(pData),
                                         vSize, fRescale, pTrans); break;
                case 32 : ApplyTFInplace(reinterpret_cast<uint32_t*>(pData),
                                         vSize, fRescale, pTrans); break;
                default : return false;
              }
              break;
      case 2 : PadInplace(pData, vSize, 3, 1, 0); break;
      default : break;
    }


    std::string strCurrentTargetFilename = SysTools::FindNextSequenceName(strCurrentDiFilename);

    return WriteImage(pData,strCurrentTargetFilename, vSize, iImageCompCount);
}
