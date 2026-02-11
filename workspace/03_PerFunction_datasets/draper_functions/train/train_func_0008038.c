SwigType_clientdata_collect(String *ms) {
  Hash *mh;
  String *clientdata = 0;

  if (r_mangleddata) {
    clientdata = Getattr(r_mangleddata, ms);
    if (clientdata)
      return clientdata;
  }

  mh = Getattr(r_mangled, ms);
  if (mh) {
    Iterator ki;
    ki = First(mh);
    while (ki.key) {
      clientdata = Getattr(r_clientdata, ki.key);
      if (clientdata)
	break;
      ki = Next(ki);
    }
  }
  return clientdata;
}
