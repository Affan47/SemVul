addProc(ConnectionIdentifier &id, int pindex, dmtcp::string hostname)
  {


    if (_hostname == "?") {
      _hostname = hostname;
    } else if (hostname != _hostname) {
      _loop = false;
    }

    if (id == _srv) {
      _sprocs.push_back(pindex);
    } else {
      _cprocs.push_back(pindex);
    }
  }
