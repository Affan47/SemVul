find(GlyphIndex leftgi, GlyphIndex rightgi) const
{
  PairOpIndex opi = find_left(leftgi);
  while (opi >= 0) {
    if (op(opi).right() == rightgi)
      return opi;
    opi = op(opi).next_left();
  }
  return -1;
}
