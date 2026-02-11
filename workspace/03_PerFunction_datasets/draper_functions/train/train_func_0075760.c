build_spiral_order(void)
{
  int i;
  int j;
  int k;
  char mark[2 * DFA_MAX_BOARD + 1][2 * DFA_MAX_BOARD + 1];
  int queue_i[DFA_MAX_ORDER];
  int queue_j[DFA_MAX_ORDER];
  int queue_start = 0;
  int queue_end = 1;

  static const int delta_i[4] = { 1,  0, -1,  0};
  static const int delta_j[4] = { 0, 1,  0,  -1};


  memset(mark, 1, sizeof(mark));
  for (i = 1; i < 2 * DFA_MAX_BOARD; i++) {
    for (j = 1; j < 2 * DFA_MAX_BOARD; j++)
      mark[i][j] = 0;
  }

  queue_i[0] = DFA_MAX_BOARD;
  queue_j[0] = DFA_MAX_BOARD;
  mark[DFA_MAX_BOARD][DFA_MAX_BOARD] = 1;

  do {
    int transformation;


    for (transformation = 0; transformation < 8; transformation++) {
      TRANSFORM2(queue_i[queue_start] - DFA_MAX_BOARD,
		 queue_j[queue_start] - DFA_MAX_BOARD,
		 &i, &j, transformation);
      spiral[queue_start][transformation] = DFA_BASE * i + j;
    }

    for (k = 0; k < 4; k++) {
      i = queue_i[queue_start] + delta_i[k];
      j = queue_j[queue_start] + delta_j[k];

      if (!mark[i][j]) {
	queue_i[queue_end] = i;
	queue_j[queue_end++] = j;
	mark[i][j] = 1;
      }
    }
  } while (++queue_start < queue_end);

  if (0) {
    int transformation;
    for (transformation = 0; transformation < 8; transformation++) {
      fprintf(stderr, "Transformation %d:\n", transformation);
      for (k = 0; k < 16; k++) {
	fprintf(stderr, "\t%d(%c); %d\n", k, 'A' + k,
		spiral[k][transformation]);
      }
    }
  }
}
