dbv_init(struct dbv *pdbv, int bits)
{


  fc_assert_ret(bits > 0 && bits < MAX_DBV_LENGTH);

  pdbv->bits = bits;
  pdbv->vec = fc_calloc(1, _BV_BYTES(pdbv->bits) * sizeof(*pdbv->vec));

  dbv_clr_all(pdbv);
}
