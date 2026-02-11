operator>> (istream & stream_, MSTypeVector<MSSymbol>::SPick & symPick_)
{
  MSSymbol sym;
  stream_ >> sym;
  symPick_._pVector->set (symPick_._index, sym);
  return stream_;
}
