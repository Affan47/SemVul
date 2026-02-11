aez_prf(Byte *res, Byte *tags [], unsigned num_tags, unsigned tag_bytes [],
                                                unsigned tau, Context *context)
{
  unsigned i, j, m = tau / 16;
  if (tau % 16 > 0) m++;
  m = max(m, 1);

  Block H, X, ctr; zero_block(ctr);
  aez_hash(H.byte, tags, num_tags, tag_bytes, context);

  for (i=0, j=0; i < m-1; i++)
  {
    xor_block(X, ctr, H);
    E(&X, X, -1, 3, context);
    cp_bytes(&res[j], X.byte, 16);
    j += 16;

    ctr.word[3] = reverse_u32(j);
  }

  xor_block(X, ctr, H);
  E(&X, X, -1, 3, context);
  cp_bytes(&res[j], X.byte, tau - j);
}
