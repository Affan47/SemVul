ParseLine(const char *buffer)
  {
    if (buffer[0] == '#')
      return;

    if (_linecount == 0)
      sscanf(buffer,"%d%d",&_nrows,&_ncols);
    else if (_linecount == 1)
      tokenize(_colnames,buffer);
    else
      {
        vector<string> vc;
        tokenize(vc,buffer);
        if (vc.size() == (unsigned)_ncols)
          _table.push_back(vc);
        else
          {
            stringstream errorMsg;
            errorMsg << " Could not parse line in type translation table types.txt -- incorect number of columns";
            errorMsg << " found " << vc.size() << " expected " << _ncols << ".";
            obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);
          }
      }
    _linecount++;
  }
