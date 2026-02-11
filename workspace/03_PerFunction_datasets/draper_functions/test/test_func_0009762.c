getState()
  {
    char ret='Z';
    if ( (value.get() & (COUTEN | CMPON)) == CMPON)
      ret = (((value.get() & CMPOUT)==CMPOUT) ^ ((value.get() & POL)==POL)) ? '0' : '1';
    if (verbose)
      cout <<"CMCON0::getState-->"<<ret << endl;
    return ret;
  }
