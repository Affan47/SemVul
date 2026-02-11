add_resources(std::list<RequestTuple*>& reqtuples,Subject* subject,ResList& resources,ActList& actions,CtxList& contexts) {
  if(resources.empty()) {
    add_actions(reqtuples,subject,NULL,actions,contexts);
    return;
  }
  ResList::iterator rit = resources.begin();
  for(;rit != resources.end();++rit) {
    add_actions(reqtuples,subject,&(*rit),actions,contexts);
  }
}
