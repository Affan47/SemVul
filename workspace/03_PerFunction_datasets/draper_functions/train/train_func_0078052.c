scope_loop_clause (NODE_T * p)
{
  if (p != NO_NODE) {
    if (IS (p, FOR_PART)) {
      scope_loop_clause (NEXT (p));
    } else if (is_one_of (p, FROM_PART, BY_PART, TO_PART, STOP)) {
      scope_statement (NEXT_SUB (p), NO_VAR);
      scope_loop_clause (NEXT (p));
    } else if (IS (p, WHILE_PART)) {
      scope_serial_clause (NEXT_SUB (p), NO_VAR, A68_TRUE);
      scope_loop_clause (NEXT (p));
    } else if (is_one_of (p, DO_PART, ALT_DO_PART, STOP)) {
      NODE_T *do_p = NEXT_SUB (p), *un_p;
      if (IS (do_p, SERIAL_CLAUSE)) {
        scope_serial_clause (do_p, NO_VAR, A68_TRUE);
        un_p = NEXT (do_p);
      } else {
        un_p = do_p;
      }
      if (un_p != NO_NODE && IS (un_p, UNTIL_PART)) {
        scope_serial_clause (NEXT_SUB (un_p), NO_VAR, A68_TRUE);
      }
    }
  }
}
