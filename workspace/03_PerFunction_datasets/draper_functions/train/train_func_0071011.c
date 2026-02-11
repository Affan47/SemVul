print_set(int *s)
{
  int i, j;
  printf("(");
  for (i = 0; i < Set_size; i++) {
    int k = s[i];
    for (j = 0; j < INT_BIT; j++) {
      if ((k>>j) & 1)
	printf("%d ", (INT_BIT * i) + j);
    }
  }
  printf(") ");
}
