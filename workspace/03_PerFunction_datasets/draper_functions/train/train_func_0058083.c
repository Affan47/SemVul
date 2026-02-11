initialize(const ParamDefs * paramdefs, const count_t paramNum) {
  for( count_t i = 0; i < paramNum; i++ ) {
    params_[paramdefs[i].name] = paramdefs[i];
  }
  cerr << "Default parameter values:\n";
  iterate(params_, itr)
    cerr << "\t" << itr->first << " --> " << itr->second.value << endl;
}
