gthgetcodon(unsigned char genomicchar1,
                          unsigned char genomicchar2,
                          unsigned char genomicchar3,
                          const GtUchar *gen_alphabet_characters,
                          const GtTransTable *transtable)
{
  char codon;
  GT_UNUSED int rval;


  rval = gt_trans_table_translate_codon(transtable,
                                        gen_alphabet_characters[genomicchar1],
                                        gen_alphabet_characters[genomicchar2],
                                        gen_alphabet_characters[genomicchar3],
                                        &codon, NULL);


  gt_assert(!rval);

  return codon;
}
