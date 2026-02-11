test_arithmetic(uint64_t rnd) {
  const uint64_t prng_mod_power = 48;
  uint64_t shifted_rnd = rnd >> (prng_mod_power - 26);
  CHECK_GE(shifted_rnd, 0);
  CHECK_LT(shifted_rnd, (1<<26));
  LOG(INFO) << shifted_rnd;
  LOG(INFO) << static_cast<double>(shifted_rnd);
  CHECK_GE(static_cast<double>(static_cast<uint32_t>(shifted_rnd)), 0);

  CHECK_GE(static_cast<double>(shifted_rnd), 0);

  double q = static_cast<double>(shifted_rnd) + 1.0;
  CHECK_GT(q, 0);
}
