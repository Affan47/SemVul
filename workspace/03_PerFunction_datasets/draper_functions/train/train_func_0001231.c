h_enddo(OMPragma* p, ostream& os) {
    int n = RExit(p);
    if ( p->is_nowait() ) {
      print_pragma(p, os);
    } else {
      p->add_nowait();
      print_pragma(p, os);
      generate_barrier(n, os);
    }
    generate_call("exit", "do", n, os);
    if ( keepSrcInfo ) reset_src_info(p, os);
  }
