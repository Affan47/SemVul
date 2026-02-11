numbered_basepair (char c, char d) {
  int c_num, d_num;
  c_num = numbered_nucleotide (c);
  d_num = numbered_nucleotide (d);
  if (c_num < 0 || d_num < 0) {
    return (-1);
  } else {
    return ((c_num << 2) | d_num);
  }
}
