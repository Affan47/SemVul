enqueueFact(const Theorem& thm) {

  TRACE("search props", "SearchEngineFast::enqueueFact(",
	thm.getExpr(), ") {");
  if(thm.isAbsLiteral()) {
    addLiteralFact(thm);
  }
  d_factQueue.push_back(thm);
  TRACE_MSG("search props", "SearchEngineFast::enqueueFact => }");
}
