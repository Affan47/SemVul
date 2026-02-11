EmptyBootloader(void) {
   int i;

   for (i = 0; i < 440; i++)
      code[i] = 0;
   nulls = 0;
}
