dvbcsa_bs_block_transpose_out (dvbcsa_bs_word_t *in,
				    const struct dvbcsa_bs_batch_s *pcks,
				    unsigned int offset)
{
  uint32_t		*ri = (uint32_t *) in;
  unsigned int		j, i, k;

  for (j = 0; j < 64; j += 16)
    for (k = 0; k < 8; k++)
      {
	dvbcsa_bs_word_t *r = in + j + k;
	dvbcsa_bs_word_t t, b;

	t = r[0];
	b = r[8];
	r[0] = BS_OR(BS_AND(t, BS_VAL16(00ff)), BS_SHL8(BS_AND(b, BS_VAL16(00ff)), 1));
	r[8] = BS_OR(BS_AND(b, BS_VAL16(ff00)), BS_SHR8(BS_AND(t, BS_VAL16(ff00)), 1));
      }

  for (j = 0; j < 64; j += 32)
    for (i = 0; i < 16; i += 8)
      for (k = 0; k < 8; k++)
	{
	  dvbcsa_bs_word_t *r = in + j + i + k;
	  dvbcsa_bs_word_t t, b;

	  t = r[0];
	  b = r[16];
	  r[0]  = BS_OR(BS_AND(t, BS_VAL32(0000ffff)), BS_SHL8(BS_AND(b, BS_VAL32(0000ffff)), 2));
	  r[16] = BS_OR(BS_AND(b, BS_VAL32(ffff0000)), BS_SHR8(BS_AND(t, BS_VAL32(ffff0000)), 2));
	}

  for (i = 0; pcks[i].data; i++)
    if (offset < (pcks[i].len & (unsigned)~0x7))
      {
	dvbcsa_store_le32(pcks[i].data + offset    , ri[i                ]);
	dvbcsa_store_le32(pcks[i].data + offset + 4, ri[i + BS_BATCH_SIZE]);
      }
}
