VisitForStatement(ForStatement* stmt) {
  stmt_ = new ForStatement(stmt,
                           DeepCopyStmt(stmt->init()),
                           DeepCopyExpr(stmt->cond()),
                           DeepCopyStmt(stmt->next()),
                           DeepCopyStmt(stmt->body()));
}
