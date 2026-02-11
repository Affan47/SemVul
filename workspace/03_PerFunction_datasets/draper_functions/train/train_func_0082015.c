score_acceptor_dinucleotide (char dinucl1, char dinucl2) {
  double score;

  debug(printf("acceptor dinucleotide %c%c  ",dinucl1,dinucl2));
  switch (dinucl1) {
  case 'A': case 'a': score = 0.9903/BACKGROUND_A; break;
  case 'C': case 'c': score = 0.0032/BACKGROUND_C; break;
  case 'G': case 'g': score = 0.0034/BACKGROUND_G; break;
  case 'T': case 't': score = 0.0030/BACKGROUND_T; break;
  default: score = 0.0001;

  }

  switch (dinucl2) {
  case 'A': case 'a': score *= 0.0027/BACKGROUND_A; break;
  case 'C': case 'c': score *= 0.0037/BACKGROUND_C; break;
  case 'G': case 'g': score *= 0.9905/BACKGROUND_G; break;
  case 'T': case 't': score *= 0.0030/BACKGROUND_T; break;
  default: score *= 0.0001;

  }

  return score;
}
