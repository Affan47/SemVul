EatsAtLeast(int still_to_find,
                          int recursion_depth,
                          bool not_at_start) {
  int answer = Length();
  if (answer >= still_to_find) return answer;
  if (recursion_depth > RegExpCompiler::kMaxRecursion) return answer;

  return answer + on_success()->EatsAtLeast(still_to_find - answer,
                                            recursion_depth + 1,
                                            true);
}
