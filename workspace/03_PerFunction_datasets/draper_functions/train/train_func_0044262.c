compare(const fillPriority &a, const fillPriority &b) {
  if(a.el < b.el) return -1;
  if(a.el > b.el) return 1;

  if(a.depth < b.depth) return -1;
  if(a.depth > b.depth) return 1;

  if(a.i < b.i) return -1;
  if(a.i > b.i) return 1;

  if(a.j < b.j) return -1;
  if(a.j > b.j) return 1;

  return 0;
}
