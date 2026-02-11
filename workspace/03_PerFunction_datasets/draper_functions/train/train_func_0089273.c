decipher(KeyDerivation& kd, uint8_t* in, uint32_t ilen, uint8_t* out, uint32_t olen, seq_nr_t seq_nr, sender_id_t sender_id, mux_t mux)
{
  std::memcpy(out, in, (ilen < olen) ? ilen : olen);
  return (ilen < olen) ? ilen : olen;
}
