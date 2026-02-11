eval(EvaluationCtx* ctx){
  Result result = DECISION_NOT_APPLICABLE;
  if(target != NULL) {
    MatchResult matchres = target->match(ctx);
    if(matchres == NO_MATCH)  return result;
    else if(matchres == INDETERMINATE) {result = DECISION_INDETERMINATE; return result;}
  }


  bool cond_res = false;
  if(condition != NULL) {
    std::list<AttributeValue*> res_list = condition->evaluate(ctx);
    AttributeValue* attrval = *(res_list.begin());

    BooleanAttribute bool_attr(true);
    if(attrval->equal(&bool_attr))
      cond_res = true;
    if(attrval) delete attrval;
    if(!cond_res) { result = DECISION_INDETERMINATE; return result; }
  }

  if (effect == "Permit") {
    result = DECISION_PERMIT;
    evalres.effect = "Permit";
  }
  else if (effect == "Deny") {
    result = DECISION_DENY;
    evalres.effect = "Deny";
  }
  return result;
}
