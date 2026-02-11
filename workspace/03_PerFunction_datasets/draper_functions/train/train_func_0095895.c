delete_speller(Speller * m)
  {
    SpellerLtHandle h = ((Speller *)(m))->lt_handle();
    delete m;
    if (h != 0) free_lt_handle(h);
  }
}
