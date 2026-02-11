SafeOpen(std::ofstream &fs, const char *filename)
  {
#ifdef WIN32
    string s(filename);
    if (s.find(".bin") != string::npos)
      fs.open(filename,ios::binary);
    else
#endif

      fs.open(filename);

    if (!fs)
      {
        string error = "Unable to open file \'";
        error += filename;
        error += "\' in write mode";
        obErrorLog.ThrowError(__FUNCTION__, error, obError);
        return(false);
      }

    return(true);
  }
