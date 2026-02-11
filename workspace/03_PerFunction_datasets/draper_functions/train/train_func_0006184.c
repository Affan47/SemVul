getConstraintType(const std::string &Constraint) const {

  if (Constraint.size() == 1) {
    switch (Constraint[0]) {
    default: break;
    case 'r': return C_RegisterClass;
    case 'm':
    case 'o':
    case 'V':
      return C_Memory;
    case 'i':
    case 'n':
    case 's':
    case 'X':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
      return C_Other;
    }
  }

  if (Constraint.size() > 1 && Constraint[0] == '{' &&
      Constraint[Constraint.size()-1] == '}')
    return C_Register;
  return C_Unknown;
}
