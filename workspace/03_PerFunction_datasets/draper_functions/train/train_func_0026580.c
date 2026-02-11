static_parameters_valid (double a, double b,
double c, double ab, double ac, double bc)
{
if (a == 0) return FALSE;
if (b == 0) return FALSE;
if (c == 0) return FALSE;
if (ab == 0) return FALSE;
if (ac == 0) return FALSE;
if (bc == 0) return FALSE;

return TRUE;
}
