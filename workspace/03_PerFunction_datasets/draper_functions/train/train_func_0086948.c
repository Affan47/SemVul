main() {
  int A = (1 << 1) + (1 << 3);
  int B = (1 << 2) + (1 << 3);
  int C = 0;


  C = A | B;


  C = A & B;


  C = A & ~B;

  int bit = 2;

  A |= (1 << bit);


  A &= ~(1 << bit);


  if (A & (1 << bit)) {

  }


  int c = __builtin_popcount(A);

  return 0;
}
