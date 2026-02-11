stack_push(stack *s, char c, int count) {
  if (s->size  && (s->chars[s->size-1] == c)) {
    s->counts[s->size-1] += count;
    return;
  }
  else {
    if (s->size == s->cap) {
      s->cap += 10;
      int *newcounts = realloc(s->counts, s->cap * sizeof(int));
      char *newchars = realloc(s->chars, s->cap);
      if (newcounts)
	s->counts = newcounts;
      else
	return;
      if (newchars)
	s->chars = newchars;
      else
	return;
    }
    s->counts[s->size] = count;
    s->chars[s->size] = c;
    s->size++;
    return;
  }
}
