scope_enclosed_clause (NODE_T * p, SCOPE_T ** s)
{
  if (IS (p, ENCLOSED_CLAUSE)) {
    scope_enclosed_clause (SUB (p), s);
  } else if (IS (p, CLOSED_CLAUSE)) {
    scope_closed_clause (SUB (p), s);
  } else if (is_one_of (p, COLLATERAL_CLAUSE, PARALLEL_CLAUSE, STOP)) {
    scope_collateral_clause (SUB (p), s);
  } else if (IS (p, CONDITIONAL_CLAUSE)) {
    scope_conditional_clause (SUB (p), s);
  } else if (is_one_of (p, CASE_CLAUSE, CONFORMITY_CLAUSE, STOP)) {
    scope_case_clause (SUB (p), s);
  } else if (IS (p, LOOP_CLAUSE)) {
    scope_loop_clause (SUB (p));
  }
}
