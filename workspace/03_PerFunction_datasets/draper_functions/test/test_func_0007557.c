LoadCurrentCharacter(int cp_offset,
                                                   Label* on_end_of_input,
                                                   bool check_bounds,
                                                   int characters) {
  ASSERT(cp_offset >= -1);
  ASSERT(cp_offset < (1<<30));
  if (check_bounds) {
    CheckPosition(cp_offset + characters - 1, on_end_of_input);
  }
  LoadCurrentCharacterUnchecked(cp_offset, characters);
}
