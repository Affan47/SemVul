enumPropertiesMess()
{
  if(m_handle) {
    gem::Properties props;
    if(!m_handle->enumProperties(props))
      return;

    int ac=0;
    t_atom ap[3];
    std::vector<std::string>keys=props.keys();

    SETFLOAT(ap+0, keys.size());
    outlet_anything(m_outInfo, gensym("numprops"), 1, ap);

    unsigned int i=0;
    for(i=0; i<keys.size(); i++) {
      ac=2;
      std::string key=keys[i];
      SETSYMBOL(ap+0, gensym(key.c_str()));
      switch(props.type(key)) {
      case gem::Properties::NONE:
        SETSYMBOL(ap+1, gensym("Bang"));
        break;
      case gem::Properties::DOUBLE: {
        double d=-1;
        SETSYMBOL(ap+1, gensym("Float"));

        if(props.get(key, d)) {
          ac=3;
          SETFLOAT(ap+2, d);
        }
      }
        break;
      case gem::Properties::STRING: {
        SETSYMBOL(ap+1, gensym("Symbol"));
        std::string s;
        if(props.get(key, s)) {
          ac=3;
          SETSYMBOL(ap+2, gensym(s.c_str()));
        }
      }
        break;
      default:
        SETSYMBOL(ap+1, gensym("unknown"));
        break;
      }
      outlet_anything(m_outInfo, gensym("property"), ac, ap);
    }
  }
}
