allot_word(cell name_, cell vocab_, cell hashcode_) {
  data_root<object> vocab(vocab_, this);
  data_root<object> name(name_, this);

  data_root<word> new_word(allot<word>(sizeof(word)), this);

  new_word->hashcode = hashcode_;
  new_word->vocabulary = vocab.value();
  new_word->name = name.value();
  new_word->def = special_objects[OBJ_UNDEFINED];
  new_word->props = false_object;
  new_word->pic_def = false_object;
  new_word->pic_tail_def = false_object;
  new_word->subprimitive = false_object;
  new_word->entry_point = NULL;

  jit_compile_word(new_word.value(), new_word->def, true);

  return new_word.untagged();
}
