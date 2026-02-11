Rank(const std::string & word,
                         mpz_class * rank) {
  (*rank) = 0;

  mpz_class e;
  mpz_ui_pow_ui(e.get_mpz_t(), 256, word.length() - 1);
  mpz_add(rank->get_mpz_t(), rank->get_mpz_t(), e.get_mpz_t());

  mpz_class in_slice_rank;
  bool retval = fte::encrypting::Base256ToMpzClass(word, word.length(), &in_slice_rank);
  mpz_add(rank->get_mpz_t(), rank->get_mpz_t(), in_slice_rank.get_mpz_t());

  return retval;
}
