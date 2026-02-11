modelHasSteadyStateProblem()
{
  int index = 0;
  while (true) {
    Parameter* ts = getParameter(index++, ECIF_TIMESTEP);
    if (ts==NULL) break;
    if ( ts->IsActive() && ts->hasFieldValueBySifName("Simulation Type", "Steady State") ) {
      return true;
    }
  }

  return false;
}
