ConvertToNative(const std::string& strRawFilename,
                                    const std::string& strTargetFilename,
                                    uint64_t iHeaderSkip,
                                    uint64_t iComponentSize,
                                    uint64_t iComponentCount, bool bSigned,
                                    bool bFloatingPoint,
                                    UINT64VECTOR3 vVolumeSize,
                                    FLOATVECTOR3 vVolumeAspect,
                                    bool bNoUserInteraction,
                                    const bool bQuantizeTo8Bit) {

  string strFormat;

  if (!bQuantizeTo8Bit) {
    if (!bFloatingPoint && bSigned && iComponentSize == 32 && iComponentCount == 1)
      strFormat = "FLOAT";
    else
    if (!bFloatingPoint && bSigned && iComponentSize == 8 && iComponentCount == 1)
      strFormat = "CHAR";
    else
    if (!bFloatingPoint && !bSigned && iComponentSize == 8 && iComponentCount == 1)
      strFormat = "UCHAR";
    else
    if (!bFloatingPoint && bSigned && iComponentSize == 16 && iComponentCount == 1)
      strFormat = "SHORT";
    else
    if (!bFloatingPoint && !bSigned && iComponentSize == 16 && iComponentCount == 1)
      strFormat = "USHORT";
    else
    if (!bFloatingPoint && !bSigned && iComponentSize == 8 && iComponentCount == 4)
      strFormat = "UCHAR4";
    else {
      T_ERROR("This data type is not supported by QVIS DAT/RAW files.");
      return false;
    }
  } else {
    if (bSigned)
      strFormat = "CHAR";
    else
      strFormat = "UCHAR";
  }


  string strTargetRAWFilename = strTargetFilename+".raw";

  ofstream fTarget(strTargetFilename.c_str());
  if (!fTarget.is_open()) {
    T_ERROR("Unable to open target file %s.", strTargetFilename.c_str());
    return false;
  }

  MESSAGE("Writing DAT File");

  fTarget << "ObjectFileName: " << SysTools::GetFilename(strTargetRAWFilename) << endl;
  fTarget << "TaggedFileName: ---" << endl;
  fTarget << "Resolution:     " << vVolumeSize.x << " " << vVolumeSize.y << " "<< vVolumeSize.z << endl;
  fTarget << "SliceThickness: " << vVolumeAspect.x << " " << vVolumeAspect.y << " "<< vVolumeAspect.z << endl;
  fTarget << "Format:         " << strFormat << endl;
  fTarget << "ObjectType:     TEXTURE_VOLUME_OBJECT" << endl;
  fTarget << "ObjectModel:    RGBA" << endl;
  fTarget << "GridType:       EQUIDISTANT" << endl;
  fTarget << "Endianness:      " << (EndianConvert::IsBigEndian() ? "BIG" : "LITTLE") << endl;

  fTarget.close();

  MESSAGE("Writing RAW File");


  bool bRAWSuccess = RAWConverter::ConvertToNative(strRawFilename, strTargetRAWFilename, iHeaderSkip,
                                                   iComponentSize, iComponentCount, bSigned, bFloatingPoint,
                                                   vVolumeSize, vVolumeAspect, bNoUserInteraction,bQuantizeTo8Bit);

  if (bRAWSuccess) {
    return true;
  } else {
    T_ERROR("Error creating raw target file %s.", strTargetRAWFilename.c_str());
    remove(strTargetFilename.c_str());
    return false;
  }
}
