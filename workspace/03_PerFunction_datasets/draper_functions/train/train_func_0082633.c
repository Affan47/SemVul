sufficient_splice_prob_distant (int support, int nmismatches, double spliceprob) {
  support -= 3*nmismatches;
  if (support < MIN_SPLICE_SUPPORT_DISTANT) {
    return 0;
  } else if (support < 30) {
    return (spliceprob > 0.95);
  } else if (support < 35) {
    return (spliceprob > 0.90);
  } else if (support < 40) {
    return (spliceprob > 0.85);
  } else {
    return (spliceprob > 0.70);
  }
}
