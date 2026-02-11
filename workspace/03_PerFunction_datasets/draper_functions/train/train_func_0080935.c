addPolicy(Policy* policy, EvaluatorContext* ctx,const std::string& id) {
  Policy* pls = dynamic_cast<Policy*>(policy);
  if(pls!=NULL) {
    pls->setEvaluatorContext(ctx);
    pls->make_policy();
    policies.push_back(PolicyElement(pls, id));
  }
}
