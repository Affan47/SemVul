gamgi_chem_orbital_radius (int n, int l, int m, double charge)
{
gamgi_radial function_r;
gamgi_angular function_a;
double za, r, ho, rho, r_max;
double constant, constant_a, constant_z, constant_r;
double d, d_old, d_old_old;
double f;

if (n < 1 || n > 6) return 0.0;
if (l < 0 || l > n - 1) return 0.0;
if (m < -l || m > l) return 0.0;

za = charge / GAMGI_CHEM_A0;
ho = 2 * za / n;
constant_z = pow (za, 1.5) * pow (ho, l);

static_radial (n, l, &constant_r, &function_r);
static_angular (l, m, &constant_a, &function_a);


r_max = GAMGI_CHEM_ORBITAL_R_MAX;

d_old = d_old_old = 0.0;
constant = constant_r * constant_z;
for (r = 0.0; r < GAMGI_CHEM_ORBITAL_R_MAX; r += GAMGI_CHEM_ORBITAL_R_STEP)
  {
  rho = r * ho;
  f = constant * exp (-rho / 2) * pow (r, l) * (*function_r) (rho);
  d = f * f * r * r;
  if (d < d_old && d_old > d_old_old)
    r_max = r - GAMGI_CHEM_ORBITAL_R_STEP;
  d_old_old = d_old;
  d_old = d;
  }


r_max += GAMGI_CHEM_ORBITAL_R_SHIFT;


constant *= constant_a;
for (r = r_max; r < GAMGI_CHEM_ORBITAL_R_MAX; r += GAMGI_CHEM_ORBITAL_R_STEP)
  {
  rho = r * ho;
  f = constant * exp (-rho / 2) * (*function_r) (rho);
  if (static_density (r, f, function_a) == FALSE) return r;
  }

return GAMGI_CHEM_ORBITAL_R_MAX;
}
