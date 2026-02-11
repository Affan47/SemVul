Base16ToBase256(const std::string & in,
                     uint32_t out_len_in_bytes,
                     unsigned char * out) {

  mpz_class tmp = mpz_class(in, 16);
  MpzClassToBase256(tmp, out_len_in_bytes, out);

  return true;
}
