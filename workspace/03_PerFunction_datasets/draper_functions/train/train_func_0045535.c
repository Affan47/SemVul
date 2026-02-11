compute_etotal()
{
  double epot,ekin,etot;
  epot = pe->compute_scalar();
  if (thermo_energy) epot -= compute_scalar();
  ekin = temperature->compute_scalar();
  ekin *= 0.5 * temperature->dof * force->boltz;
  etot = epot+ekin;
  return etot;
}
