print_pf( std::ostream& s, int ind ){

  if( d_pvRpl.get()!=d_pv.get() ){
    d_letPfRpl->fillHoles();
  }
  s << "(" << (d_isTh ? "th_let_pf _ " : "satlem _ _ _ " );
  d_letPfRpl->print( s );
  s << "(\\ ";
  d_pv->print( s );
  s << " " << endl;
  lambdaPrintMap[d_letPf.get()]=d_pvRpl.get();
  d_body->print( s, ind );
  lambdaPrintMap[d_letPf.get()]=NULL;
  s << "))";
}
