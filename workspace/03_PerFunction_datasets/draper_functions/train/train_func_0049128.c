run_to_address (unsigned int destination)
{


  if(simulation_mode != eSM_STOPPED) {
    if(verbose)
      cout << "Ignoring run-to-address request because simulation is not stopped\n";
    return;
  }


  unsigned int bp_num = bp.set_execution_break(this, destination);
  run();
  bp.clear(bp_num);

}
