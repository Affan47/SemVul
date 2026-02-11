spliceEndSignal(unsigned coordinate,
				       char strand) const {
  if (strand == '+') {
    const uchar *genomeBeg = genome.seqReader();
    const uchar *p = genomeBeg + coordinate;
    unsigned n2 = alphabet.canonical[*(p - 1)];
    if (n2 >= 4) return 16;
    unsigned n1 = alphabet.canonical[*(p - 2)];
    if (n1 >= 4) return 16;
    return n1 * 4 + n2;
  } else {
    const uchar *genomeEnd = genome.seqReader() + genome.finishedSize();
    const uchar *p = genomeEnd - coordinate;
    unsigned n2 = alphabet.canonical[*p];
    if (n2 >= 4) return 16;
    unsigned n1 = alphabet.canonical[*(p + 1)];
    if (n1 >= 4) return 16;
    return 15 - (n1 * 4 + n2);
  }
}
