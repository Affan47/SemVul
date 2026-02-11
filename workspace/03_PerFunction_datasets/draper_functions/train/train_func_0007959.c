Rescale(string text)
  {


    if (! IsUnits(text) ){
      errorMsg << "Problems reading GUK input - bad scale factor: " << text;
      obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
      return -1.0;
    }

    if (text.compare(0, 4, "angs")==0) {
      return 1.0;
    } else if (text.compare(0, 4, "bohr")==0||text.compare(0, 4, "a.u.")==0
               ||text.compare(0, 2, "au")==0) {
      return BOHR_TO_ANGSTROM;
    } else {
      return -1.0;
    }
  }
