dephase()
{
  bigint ntimestep_hold = update->ntimestep;

  update->whichflag = 1;
  update->nsteps = n_dephase*t_dephase;

  timer->barrier_start(TIME_LOOP);

  for (int i = 0; i < n_dephase; i++) {
    int seed = static_cast<int> (random_dephase->uniform() * MAXSMALLINT);
    if (seed == 0) seed = 1;
    velocity->create(temp_dephase,seed);
    update->integrate->run(t_dephase);
    if (temp_flag == 0) temp_dephase = temperature->compute_scalar();
  }

  timer->barrier_stop(TIME_LOOP);
  time_dephase += timer->array[TIME_LOOP];

  update->integrate->cleanup();
  finish->end(0);


  update->ntimestep = ntimestep_hold;
  for (int i = 0; i < modify->ncompute; i++)
    if (modify->compute[i]->timeflag) modify->compute[i]->clearstep();
}
