zScoreScanners(zTrellis *trellis, zStrIdx name, const char *state_name,
					   coor_t start, coor_t end, bool ps, int *do_return, int *flag){


  zSfeature f;
  zScanner *scanner;
  zScanner *c_scanner;
  zScanner *nc_scanner;
  coor_t dna_len;
  score_t score;
  char  s;
  int fl2;
  s = *state_name;
  fl2 = *flag;
  zSetScanners(&scanner, &c_scanner, &nc_scanner,
               trellis, name, ps);

  dna_len = trellis->dna->length;


  f.name = name;
  f.lfrag = 0;
  f.rfrag = 0;
  f.frame = 0;

  f.start = (ps) ? start : (dna_len-end-1);
  f.end = (ps) ? end : (dna_len-start-1);
  score = 0.;

  if (scanner != NULL) score += scanner->scoref(scanner, &f);


  if (c_scanner != NULL) score += c_scanner->scoref(c_scanner, &f);

  *do_return = 0;

  return score;
}
