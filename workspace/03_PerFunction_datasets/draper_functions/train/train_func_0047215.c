quant_prefix(Pterm start, Pterm end)
{
  return
    quantifier(start->t) &&
    start->next != end &&
    ordinary_constant(start->next->t);
}
