dvbcsa_bs_block_decrypt_batch(const struct dvbcsa_bs_key_s *key,
				   const struct dvbcsa_bs_batch_s *pcks,
				   unsigned int maxlen)
{
  unsigned int	i;


  dvbcsa_bs_block_decrypt_block(key, pcks, 0);

  for (i = 8; i < maxlen; i += 8)
    {
      unsigned int	g;


      for (g = 0; pcks[g].data; g++)
	if (i < (pcks[g].len & (unsigned)~0x7))
	  dvbcsa_xor_64(pcks[g].data + i - 8, pcks[g].data + i);


      dvbcsa_bs_block_decrypt_block(key, pcks, i);
    }
}
