timestep()
{
  if (narg != 1) error->all(FLERR,"Illegal timestep command");
  update->dt = force->numeric(FLERR,arg[0]);
}
