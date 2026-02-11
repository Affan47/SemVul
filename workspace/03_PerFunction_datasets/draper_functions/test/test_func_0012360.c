bbt(Formula f, int start, int end)
{
  if (start == end)
    return f->kids[start];
  else {
    int mid = (start + end) / 2;
    Formula b = formula_get(2, f->type);
    b->kids[0] = bbt(f, start, mid);
    b->kids[1] = bbt(f, mid+1, end);
    return b;
  }
}
