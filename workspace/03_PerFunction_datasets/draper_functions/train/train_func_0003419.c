ReadFile(OBBase* pOb, std::string filePath)
  {
    if(!pInFormat) return false;


    InFilename = filePath;


    if (pInStream && NeedToFreeInStream) {
      delete pInStream;
    }

    ifstream *ifs = new ifstream;
    NeedToFreeInStream = true;

    ios_base::openmode imode = ios_base::in|ios_base::binary;


    ifs->open(filePath.c_str(),imode);
    if(!ifs || !ifs->good())
      {
        obErrorLog.ThrowError(__FUNCTION__,"Cannot read from " + filePath, obError);
        return false;
      }

    return Read(pOb,ifs);
  }
