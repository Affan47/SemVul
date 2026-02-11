gabufr_parse_f0(gabufr_parseinf * inf, gaint x, gaint y) {
  gabufr_val * val;
  gabufr_val delrepval;
  gabufr_varinf * varinf;
  gaint numdesc, numreps;

  if (x == 0 && y == 0) {
    if (GABUFR_DEBUG) printf("null descriptor\n");
    return GABUFR_OK;
  } else {
    varinf = gabufr_get_varinf(x, y);
    if (GABUFR_DEBUG) printf("\t%s\n", varinf->description);
  }

  if (inf->delrep) {
    if ( x != 31 ) {
      printf("error: expected F=0 Y=31 X=... for delayed replication\n");
      return GABUFR_ERR;
    }
    if (gabufr_parseval(inf, x, y, &delrepval) == GABUFR_ERR) {
      return GABUFR_ERR;
    }
    numreps = delrepval.val;
    numdesc = inf->delrep;
    inf->delrep = 0;
    if (gabufr_replicate(inf, numdesc, numreps) == GABUFR_ERR) {
      return GABUFR_ERR;
    }
  } else {
    val = (gabufr_val *) malloc(sizeof(gabufr_val));
    if (val == NULL) {
      printf("Memory allocation failed during parsing\n");
      return GABUFR_ERR;
    }
    if (gabufr_parseval(inf, x, y, val) == GABUFR_ERR) {
      return GABUFR_ERR;
    }
    gabufr_addval(inf, val);
  }
  return GABUFR_OK;
}
