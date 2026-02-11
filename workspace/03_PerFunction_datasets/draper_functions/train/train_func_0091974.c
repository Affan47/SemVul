dcc_remove_lost(void)
{
  int i;

  for (i = 0; i < dcc_total; i++) {
    if (dcc[i].type == &DCC_LOST) {
      dcc[i].type = NULL;
      dcc[i].sock = -1;
      removedcc(i);
      i--;
    }
  }
}
