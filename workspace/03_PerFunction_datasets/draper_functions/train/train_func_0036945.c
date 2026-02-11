VisitForEffect(Expression* expr) {
  EffectContext for_effect(this);
  Visit(expr);
}
