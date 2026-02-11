setSymbol(const unsigned int argc, const t_atom*argv) {
  char buf[MAXPDSTRING];
  std::string name;
  bool firsttime=true;

  unsigned int i;
  for(i=0; i<argc; i++) {
    t_atom*arg=(t_atom*)(argv+i);
    std::string atomname;
    if(A_FLOAT==argv[i].a_type) {
      snprintf(buf, MAXPDSTRING, "%g", atom_getfloat(arg));
      buf[MAXPDSTRING-1]=0;
      atomname=buf;
    } else {
      atomname=std::string(atom_getsymbol(arg)->s_name);
    }
    if(!firsttime)
      name+=" ";
    firsttime=false;
    name+=atomname;
  }

  m_pimpl->sym=gensym(name.c_str());
  return (*this);
}
