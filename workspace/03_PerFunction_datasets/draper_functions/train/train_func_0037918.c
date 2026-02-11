step_simulation (int nSteps)
{
  Processor *cpu = get_active_cpu();

  if (cpu)
    cpu->step(nSteps);

}
