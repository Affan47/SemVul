makePositionSpecificExpMatrix(const OneQualityExpMatrix &m,
                                   const uchar *sequenceBeg,
                                   const uchar *sequenceEnd,
                                   const uchar *qualityBeg,
                                   double *destinationBeg) {
  while (sequenceBeg < sequenceEnd) {
    int letter2 = *sequenceBeg++;
    int quality2 = *qualityBeg++;
    for (int letter1 = 0; letter1 < scoreMatrixRowSize; ++letter1)
      *destinationBeg++ = m(letter1, letter2, quality2);
  }
}
