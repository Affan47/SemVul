add_actions(std::list<RequestTuple*>& reqtuples,Subject* subject,Resource* resource,ActList& actions,CtxList& contexts) {
  if(actions.empty()) {
    add_contexts(reqtuples,subject,resource,NULL,contexts);
    return;
  }
  ActList::iterator ait = actions.begin();
  for(;ait != actions.end();++ait) {
    add_contexts(reqtuples,subject,resource,&(*ait),contexts);
  }
}
