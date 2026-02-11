BiggestPowerTen(uint32_t number,
                            int number_bits,
                            uint32_t* power,
                            int* exponent_plus_one) {
  ASSERT(number < (1u << (number_bits + 1)));

  int exponent_plus_one_guess = ((number_bits + 1) * 1233 >> 12);


  exponent_plus_one_guess++;


  while (number < kSmallPowersOfTen[exponent_plus_one_guess]) {
    exponent_plus_one_guess--;
  }
  *power = kSmallPowersOfTen[exponent_plus_one_guess];
  *exponent_plus_one = exponent_plus_one_guess;
}
