ParseLocalName(State *state) {
  State copy = *state;
  if (ParseChar(state, 'Z') && ParseEncoding(state) &&
      ParseChar(state, 'E') && MaybeAppend(state, "::") &&
      ParseName(state) && Optional(ParseDiscriminator(state))) {
    return true;
  }
  *state = copy;

  if (ParseChar(state, 'Z') && ParseEncoding(state) &&
      ParseTwoChar(state, "Es") && Optional(ParseDiscriminator(state))) {
    return true;
  }
  *state = copy;
  return false;
}
