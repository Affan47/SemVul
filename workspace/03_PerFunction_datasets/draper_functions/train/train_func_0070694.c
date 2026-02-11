genie_dyad_upb (NODE_T * p)
{
  A68_REF z;
  A68_ARRAY *x;
  A68_TUPLE *t;
  A68_INT k;
  POP_REF (p, &z);

  DECREMENT_STACK_POINTER (p, A68_UNION_SIZE);
  CHECK_REF (p, z, MODE (ROWS));
  POP_OBJECT (p, &k, A68_INT);
  GET_DESCRIPTOR (x, t, &z);
  if (VALUE (&k) < 1 || VALUE (&k) > DIM (x)) {
    diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_INVALID_DIMENSION, (int) VALUE (&k));
    exit_genie (p, A68_RUNTIME_ERROR);
  }
  PUSH_PRIMITIVE (p, UPB (&(t[VALUE (&k) - 1])), A68_INT);
}
