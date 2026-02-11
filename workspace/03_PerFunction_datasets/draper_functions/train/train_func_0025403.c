static_chemical_Cn (char *group, gamgi_symmetry *symmetry)
{
int n, order_C;

if (symmetry->n_i != 0) return;
n = order_C = symmetry->C[0]->order;
while (n > 1)
  {
  if (order_C % n == 0 && symmetry->sum_C[n] != 1) return;
  if (order_C % n != 0 && symmetry->sum_C[n] != 0) return;
  n--;
  }

sprintf (group, "C%d", order_C);
if (symmetry->periodic == FALSE) return;

sprintf (group, "%d C%d", order_C, order_C);

if (order_C > 6 || order_C == 5) static_space_Cn  (group, symmetry);
}
