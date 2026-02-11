get_base_from_symbol(GtHcrSeqDecoder *seq_dec,
                                 unsigned long symbol)
{
  unsigned char base = (unsigned char) symbol % seq_dec->alphabet_size;
  if (base == (unsigned char) seq_dec->alphabet_size)
    return (unsigned char) WILDCARD;
  return base;
}
