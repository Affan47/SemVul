ParseArrayType(State *state) {
  State copy = *state;
  if (ParseChar(state, 'A') && ParseNumber(state) &&
      ParseChar(state, '_') && ParseType(state)) {
    return true;
  }
  *state = copy;

  if (ParseChar(state, 'A') && Optional(ParseExpression(state)) &&
      ParseChar(state, '_') && ParseType(state)) {
    return true;
  }
  *state = copy;
  return false;
}
