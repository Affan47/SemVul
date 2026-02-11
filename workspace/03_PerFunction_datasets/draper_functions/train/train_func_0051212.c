get_replicator_value (NODE_T * p, BOOL_T check)
{
  int z = 0;
  if (IS (p, STATIC_REPLICATOR)) {
    A68_INT u;
    if (genie_string_to_value_internal (p, MODE (INT), NSYMBOL (p), (BYTE_T *) & u) == A68_FALSE) {
      diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_IN_DENOTATION, MODE (INT));
      exit_genie (p, A68_RUNTIME_ERROR);
    }
    z = VALUE (&u);
  } else if (IS (p, DYNAMIC_REPLICATOR)) {
    A68_INT u;
    EXECUTE_UNIT (NEXT_SUB (p));
    POP_OBJECT (p, &u, A68_INT);
    z = VALUE (&u);
  } else if (IS (p, REPLICATOR)) {
    z = get_replicator_value (SUB (p), check);
  }
  if (check && z < 0) {
    diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_FORMAT_INVALID_REPLICATOR);
    exit_genie (p, A68_RUNTIME_ERROR);
  }
  return (z);
}
