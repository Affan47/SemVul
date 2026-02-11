compute_prob (int exonlen, int intronlen, int indexsize) {
  double prob;

  if (exonlen < indexsize) {
    prob = 1.0;
  } else {
    prob = 1 - pow(1.0-pow(4.0,(double) -exonlen),(double) intronlen);
  }
  debug(printf("Probability of exon of length %d (indexsize %d) with intron of length %d is %g\n",
	       exonlen,indexsize,intronlen,prob));
  return prob;
}
