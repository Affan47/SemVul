CheckFP()
  {

    OBFingerprint* pFP = OBFingerprint::FindFingerprint(header.fpid);
    if(!pFP)
      {
        stringstream errorMsg;
        errorMsg << "Index has Fingerprints of type '" << header.fpid
                 << " which is not currently loaded." << endl;
        obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
      }
    return pFP;
  }
