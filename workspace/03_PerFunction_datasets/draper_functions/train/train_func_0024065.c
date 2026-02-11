update (lrs_dic * P, lrs_dat * Q, long *i, long *j)


{

  long leave, enter;

  long *B = P->B;
  long *C = P->C;
  long *Row = P->Row;
  long *Col = P->Col;
  long m = P->m;
  long d = P->d;

  leave = B[*i];
  enter = C[*j];
  B[*i] = enter;
  reorder1 (B, Row, *i, m + 1);
  C[*j] = leave;
  reorder1 (C, Col, *j, d);

  for (*i = 1; B[*i] != enter; (*i)++);
  for (*j = 0; C[*j] != leave; (*j)++);
}
