destroy (PointCutExpr * expr) {
  if (!expr) return;
  expr->ref(-1);
  if (expr->get_ref () == 0) {
    for (int i = 0; i < expr->args (); i++)
      destroy (expr->arg (i));
    delete expr;
  }
}
