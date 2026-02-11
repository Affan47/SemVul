compose(unsigned a, unsigned b) const {
  if (!a) return b;
  if (!b) return a;
  return tri_.composeSubRegIndices(a, b);
}
