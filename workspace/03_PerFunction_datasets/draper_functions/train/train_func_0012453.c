enumerate_keys(OVECTOR table) {
  VECTOR result = newvector_noinit(NUM(AT(table, 0)));
  int i;
  int j = 0;

  for (i = 1; i < table->_.length; i++) {
    OVECTOR link = (OVECTOR) AT(table, i);

    while (link != NULL) {
      ATPUT(result, j, AT(link, HASHLINK_NAME));
      j++;
      link = (OVECTOR) AT(link, HASHLINK_NEXT);
    }
  }

  return result;
}
