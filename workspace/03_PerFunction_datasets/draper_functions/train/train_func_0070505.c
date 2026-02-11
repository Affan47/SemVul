parmMess(int key, int argc, t_atom *argv){
  unsigned int realkey=0;
  if(!m_plugin) {
    error("no plugin present! forgetting parameter....");
    return;
  }
  if(key<=0) {
    error("parameterIDs must be >0");
    return;
  } else {
    realkey=key-1;
  }
  if(static_cast<unsigned int>(key)>=m_plugin->m_parameterNames.size()) {
    error("parameterID out of bounds");
    return;
  }

  int type=m_plugin->m_parameterTypes[key];

  double r, g, b;
  double x, y;

  const char*name=m_plugin->m_parameterNames[key].c_str();
  switch(type) {
  case(F0R_PARAM_BOOL):
    if(argc!=1) {
      error("param#%02d('%s') is of type BOOL: need exactly 1 argument", key, name);
      return;
    }
    m_plugin->set(realkey, (atom_getfloat(argv)>0.5));
    break;
  case(F0R_PARAM_DOUBLE):
    if(argc!=1) {
      error("param#%02d('%s') is of type DOUBLE: need exactly 1 argument", key, name);
      return;
    }
    m_plugin->set(realkey, static_cast<double>(atom_getfloat(argv)));
    break;
  case(F0R_PARAM_COLOR):
    if(argc!=3) {
      error("param#%02d('%s') is of type COLOR: need exactly 3 arguments", key, name);
      return;
    }
    r=atom_getfloat(argv+0);
    g=atom_getfloat(argv+1);
    b=atom_getfloat(argv+2);
    m_plugin->set(realkey, r, g, b);
    break;
  case(F0R_PARAM_POSITION):
    if(argc!=2) {
      error("param#%02d('%s') is of type POSITION: need exactly 2 arguments", key, name);
      return;
    }
    x=atom_getfloat(argv+0);
    y=atom_getfloat(argv+1);
    m_plugin->set(realkey, x, y);
    break;
  case(F0R_PARAM_STRING):
    if(argc!=1) {
      error("param#%02d('%s') is of type STRING: need exactly 1 argument", key, name);
      return;
    }
    m_plugin->set(realkey, std::string(atom_getsymbol(argv)->s_name));
    break;
  default:
    error("param#%02d('%s') is of UNKNOWN type", key, name);
    break;
  }

}
