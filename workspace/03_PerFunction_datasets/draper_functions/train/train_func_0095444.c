VisitRegExpLiteral(RegExpLiteral* expr) {
  HRegExpLiteral* instr = new HRegExpLiteral(expr->pattern(),
                                             expr->flags(),
                                             expr->literal_index());
  ast_context()->ReturnInstruction(instr, expr->id());
}
