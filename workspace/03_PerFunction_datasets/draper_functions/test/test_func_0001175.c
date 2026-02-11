lookup_constraint (const char *str)
{
  switch (str[0])
    {
    case 'A':
      return CONSTRAINT_A;
    case 'B':
      return CONSTRAINT_B;
    case 'C':
      return CONSTRAINT_C;
    case 'D':
      return CONSTRAINT_D;
    case 'I':
      return CONSTRAINT_I;
    case 'J':
      return CONSTRAINT_J;
    case 'K':
      return CONSTRAINT_K;
    case 'L':
      return CONSTRAINT_L;
    case 'M':
      return CONSTRAINT_M;
    case 'N':
      return CONSTRAINT_N;
    case 'O':
      return CONSTRAINT_O;
    case 'P':
      return CONSTRAINT_P;
    case 'R':
      return CONSTRAINT_R;
    case 'T':
      return CONSTRAINT_T;
    case 'U':
      return CONSTRAINT_U;
    case 'W':
      return CONSTRAINT_W;
    case 'a':
      return CONSTRAINT_a;
    case 'b':
      return CONSTRAINT_b;
    case 'd':
      return CONSTRAINT_d;
    case 'f':
      return CONSTRAINT_f;
    case 'q':
      return CONSTRAINT_q;
    default: break;
    }
  return CONSTRAINT__UNKNOWN;
}
