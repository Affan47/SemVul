SkipPass(int int_pass, bool ignore_case) {
  TextEmitPassType pass = static_cast<TextEmitPassType>(int_pass);
  if (ignore_case) {
    return pass == SIMPLE_CHARACTER_MATCH;
  } else {
    return pass == NON_LETTER_CHARACTER_MATCH || pass == CASE_CHARACTER_MATCH;
  }
}
