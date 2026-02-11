genie_repr_char (NODE_T * p)
{
  A68_INT k;
  POP_OBJECT (p, &k, A68_INT);
  PRELUDE_ERROR (VALUE (&k) < 0 || VALUE (&k) > (int) UCHAR_MAX, p, ERROR_OUT_OF_BOUNDS, MODE (CHAR));
  PUSH_PRIMITIVE (p, (char) (VALUE (&k)), A68_CHAR);
}
