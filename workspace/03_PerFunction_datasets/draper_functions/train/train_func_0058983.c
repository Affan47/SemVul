genie_add_long_bytes (NODE_T * p)
{
  A68_LONG_BYTES *i, *j;
  POP_OPERAND_ADDRESSES (p, i, j, A68_LONG_BYTES);
  PRELUDE_ERROR (((int) strlen (VALUE (i)) + (int) strlen (VALUE (j))) > LONG_BYTES_WIDTH, p, ERROR_OUT_OF_BOUNDS, MODE (LONG_BYTES));
  bufcat (VALUE (i), VALUE (j), LONG_BYTES_WIDTH);
}
