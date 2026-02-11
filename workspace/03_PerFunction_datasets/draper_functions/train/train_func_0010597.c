h_inst(OMPragma* p, ostream& os) {
    char c1 = toupper(p->name.substr(4)[0]);
    if ( lang & L_FORTRAN )
      os << "      call POMP_" << c1 << p->name.substr(5) << "()\n";
    else
      os << "POMP_" << c1 << p->name.substr(5) << "();\n";
    if ( keepSrcInfo ) reset_src_info(p, os);
  }
