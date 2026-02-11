explicit_time_strategy(MESH *mesh, ADAPT_INSTAT *adapt)
{
  FUNCNAME("explicit_time_strategy");
  ADAPT_STAT *adapt_s = adapt->adapt_space;


  if (adapt->time <= adapt->start_time) {
    if (adapt_s->estimate)
      adapt_s->estimate(mesh, adapt_s);
  }

  adapt->time += adapt->timestep;
  if (adapt->set_time)
    adapt->set_time(mesh, adapt);

  INFO(adapt->info,6,"time = %.4le, timestep = %.4le\n", adapt->time, adapt->timestep);

  adapt_mesh(mesh, adapt_s);

  if (adapt_s->solve)
    adapt_s->solve(mesh);

  if (adapt_s->estimate)
    adapt_s->estimate(mesh, adapt_s);

  return;
}
