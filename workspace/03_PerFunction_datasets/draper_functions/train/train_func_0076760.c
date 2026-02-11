jerasure_dumb_bitmatrix_to_schedule(int k, int m, int w, int *bitmatrix)
{
  int **operations;
  int op;
  int index, optodo, i, j;

  operations = talloc(int *, k*m*w*w+1);
  op = 0;

  index = 0;
  for (i = 0; i < m*w; i++) {
    optodo = 0;
    for (j = 0; j < k*w; j++) {
      if (bitmatrix[index]) {
        operations[op] = talloc(int, 5);
        operations[op][4] = optodo;
        operations[op][0] = j/w;
        operations[op][1] = j%w;
        operations[op][2] = k+i/w;
        operations[op][3] = i%w;
        optodo = 1;
        op++;

      }
      index++;
    }
  }
  operations[op] = talloc(int, 5);
  operations[op][0] = -1;
  return operations;
}
