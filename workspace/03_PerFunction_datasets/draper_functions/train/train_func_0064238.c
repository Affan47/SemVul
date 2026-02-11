gt_trans_table_is_stop_codon(const GtTransTable *tt,
                                  char c1, char c2, char c3)
{
  char trans;
  gt_assert(tt);
  trans = codon2amino(tt->scheme->aminos, true,
                      (unsigned char) c1,
                      (unsigned char) c2,
                      (unsigned char) c3,
                      NULL, NULL);
  if (trans == GT_STOP_AMINO) {
    return true;
  }
  return false;
}
