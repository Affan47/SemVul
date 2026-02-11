store_8mers_rev_partial (int sequencepos, Genomicpos_T **pointers, int *counts,
			 UINT4 low_rc, UINT4 high_rc, UINT4 nextlow_rc,
			 int startdiscard, int enddiscard) {
  UINT4 masked;
  int pos;

  pos = enddiscard;

  while (pos >= startdiscard && pos >= 25) {
    masked = high_rc >> (2*pos - 32);
    masked |= nextlow_rc << (64 - 2*pos);
    masked &= MASK8;
    if (counts[masked]) { *(pointers[masked]++) = (Genomicpos_T) sequencepos; }
    sequencepos++;
    pos--;
  }

  while (pos >= startdiscard && pos >= 16) {
    masked = high_rc >> (2*pos - 32);
    masked &= MASK8;
    if (counts[masked]) { *(pointers[masked]++) = (Genomicpos_T) sequencepos; }
    sequencepos++;
    pos--;
  }

  while (pos >= startdiscard && pos >= 9) {
    masked = low_rc >> 2*pos;
    masked |= high_rc << (32 - 2*pos);
    masked &= MASK8;
    if (counts[masked]) { *(pointers[masked]++) = (Genomicpos_T) sequencepos; }
    sequencepos++;
    pos--;
  }

  while (pos >= startdiscard) {
    masked = low_rc >> 2*pos;
    masked &= MASK8;
    if (counts[masked]) { *(pointers[masked]++) = (Genomicpos_T) sequencepos; }
    sequencepos++;
    pos--;
  }

  return sequencepos;
}
