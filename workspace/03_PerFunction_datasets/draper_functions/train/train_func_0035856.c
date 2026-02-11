get_max_char(ntCounts n) {
  int max = n.G;
  char max_char = 'G';

  if (n.A > max) {
	max = n.A;
	max_char = 'A';
  }
  else if (n.T > max) {
	max = n.T;
	max_char = 'T';
  }
  else if (n.C > max) {
	max = n.C;
	max_char = 'C';
  }
  else if (n.gap > max) {
	max = n.gap;
	max_char = '-';
  }

  return (max_char);
}
