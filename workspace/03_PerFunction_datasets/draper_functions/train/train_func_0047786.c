VisitSwitchStatement(SwitchStatement* stmt) {
  BitVector result(av_);
  av_.Clear();
  Visit(stmt->tag());
  result.Union(av_);
  for (int i = 0; i < stmt->cases()->length(); i++) {
    CaseClause* clause = stmt->cases()->at(i);
    if (!clause->is_default()) {
      av_.Clear();
      Visit(clause->label());
      result.Union(av_);
    }
    VisitStatements(clause->statements());
  }
  av_.Union(result);
}
