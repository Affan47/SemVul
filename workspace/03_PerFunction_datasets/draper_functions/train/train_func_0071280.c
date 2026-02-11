getPropertyMess(int argc, t_atom*argv)
{
  if(argc) {
    int i=0;
    m_readprops.clear();

    for(i=0; i<argc; i++) {
      addProperties(m_readprops, 1, argv+i);
    }

  } else {

  }

  t_atom ap[4];
  if(m_videoHandle) {
    m_videoHandle->getProperties(m_readprops);
    std::vector<std::string>keys=m_readprops.keys();
    unsigned int i=0;
    for(i=0; i<keys.size(); i++) {
      std::string key=keys[i];
      SETSYMBOL(ap+0, gensym(key.c_str()));
      int ac=0;
      switch(m_readprops.type(key)) {
      default:
      case gem::Properties::UNSET:
        ac=0;
        break;
      case gem::Properties::NONE:
        ac=1;
        break;
      case gem::Properties::DOUBLE:
        do {
          double d=0;
          if(m_readprops.get(key, d)) {
            ac=2;
            SETFLOAT(ap+1, d);
          }
        } while(0);
        break;
      case gem::Properties::STRING:
        do {
          std::string s;
          if(m_readprops.get(key, s)) {
            ac=2;
            SETSYMBOL(ap+1, gensym(s.c_str()));
          }
        } while(0);
        break;
      }
      if(ac) {
        outlet_anything(m_infoOut, gensym("prop"), ac, ap);
      } else {
        post("oops: %s", key.c_str());
      }
    }
  } else {
    verbose(1, "no open videodevice...remembering properties...");
  }
}
