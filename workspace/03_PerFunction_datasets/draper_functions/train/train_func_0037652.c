getConstraintType(StringRef Constraint) const {
  unsigned S = Constraint.size();

  if (S == 1) {
    switch (Constraint[0]) {
    default: break;
    case 'r': return C_RegisterClass;
    case 'm':
    case 'o':
    case 'V':
      return C_Memory;
    case 'i':
    case 'n':
    case 'E':
    case 'F':
    case 's':
    case 'p':
    case 'X':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case '<':
    case '>':
      return C_Other;
    }
  }

  if (S > 1 && Constraint[0] == '{' && Constraint[S-1] == '}') {
    if (S == 8 && Constraint.substr(1, 6) == "memory")
      return C_Memory;
    return C_Register;
  }
  return C_Unknown;
}
