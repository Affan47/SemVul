memory_report(FILE *fp)
{
  int i;
  fprintf(fp, "\nMemory report, %d @ %d = %d megs (%.2f megs used).\n",
	  Malloc_calls, MALLOC_MEGS, Malloc_calls * MALLOC_MEGS,
	  Bytes_palloced / (1024 * 1024.0));
  for (i = 0; i < MAX_MEM_LISTS; i++) {
    int n = mlist_length(M[i]);
    if (n != 0)
      fprintf(fp, "List %3d, length %7d, %8.1f K\n", i, n,
	      i * n * BYTES_POINTER / 1024.);
  }
}
