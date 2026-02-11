mode_check_variable_declaration (NODE_T * p)
{
  if (p != NO_NODE) {
    switch (ATTRIBUTE (p)) {
    case DECLARER:
      {
        mode_check_declarer (SUB (p));
        mode_check_variable_declaration (NEXT (p));
        break;
      }
    case DEFINING_IDENTIFIER:
      {
        if (whether (p, DEFINING_IDENTIFIER, ASSIGN_SYMBOL, UNIT, STOP)) {
          SOID_T x, y;
          make_soid (&x, STRONG, SUB_MOID (p), 0);
          mode_check_unit (NEXT_NEXT (p), &x, &y);
          if (!is_coercible_in_context (&y, &x, FORCE_DEFLEXING)) {
            cannot_coerce (p, MOID (&y), MOID (&x), STRONG, FORCE_DEFLEXING, UNIT);
          } else if (SUB_MOID (&x) != MOID (&y)) {

            semantic_pitfall (NEXT_NEXT (p), MOID (&x), VARIABLE_DECLARATION, GENERATOR);
          }
        }
        break;
      }
    default:
      {
        mode_check_variable_declaration (SUB (p));
        mode_check_variable_declaration (NEXT (p));
        break;
      }
    }
  }
}
