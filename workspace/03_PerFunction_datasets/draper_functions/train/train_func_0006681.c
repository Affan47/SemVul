scale(int narg, char **arg)
{
  double t_desired = force->numeric(FLERR,arg[0]);


  int tflag = 0;
  if (temperature == NULL) {
    char **arg = new char*[3];
    arg[0] = (char *) "velocity_temp";
    arg[1] = group->names[igroup];
    arg[2] = (char *) "temp";
    temperature = new ComputeTemp(lmp,3,arg);
    tflag = 1;
    delete [] arg;
  }


  if (igroup != temperature->igroup && comm->me == 0)
    error->warning(FLERR,"Mismatch between velocity and compute groups");
  temperature->init();
  temperature->setup();


  double t = temperature->compute_scalar();
  rescale(t,t_desired);


  if (tflag) delete temperature;
}
