operator<<( ostream &out, CFG &cfg ) {
  out << "define i32 @" << cfg.name << "(";

  for (int i = 0; i < cfg.params.size(); i++) {
    out << "i32 %" << cfg.params[i] << "_0" ;
    if (i != cfg.params.size() - 1)
      out << ",";
  }
  out << ")" << endl;

  out << "{" << endl;
  vector<BasicBlock*>::iterator it;

  for ( it = cfg.blocks.begin(); it < cfg.blocks.end(); it++ ) {
    out << **it;
  }

  out << "}" << endl;
  return out;
}
