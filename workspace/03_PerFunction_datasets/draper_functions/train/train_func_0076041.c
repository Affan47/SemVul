word_start(int i) const {
  if (input_type() == FL_SECRET_INPUT) return 0;


  while (i > 0 && isword(index(i-1))) i--;
  return i;
}
