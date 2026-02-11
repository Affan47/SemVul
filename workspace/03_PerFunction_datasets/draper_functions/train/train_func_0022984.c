portcheck (NODE_T * p)
{
  for (; p != NO_NODE; FORWARD (p)) {
    portcheck (SUB (p));
    if (OPTION_PORTCHECK (&program)) {
      if (IS (p, INDICANT) && MOID (p) != NO_MOID) {
        PORTCHECK_TAX (p, PORTABLE (MOID (p)));
        PORTABLE (MOID (p)) = A68_TRUE;
      } else if (IS (p, IDENTIFIER)) {
        PORTCHECK_TAX (p, PORTABLE (TAX (p)));
        PORTABLE (TAX (p)) = A68_TRUE;
      } else if (IS (p, OPERATOR)) {
        PORTCHECK_TAX (p, PORTABLE (TAX (p)));
        PORTABLE (TAX (p)) = A68_TRUE;
      }
    }
  }
}
