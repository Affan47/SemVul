init_uci_options() {
  Option *o;

  o = option_with_name("Threads");
  assert(o != NULL);


  sprintf(o->defaultValue, "%d", Min(cpu_count(), 7));
  sprintf(o->currentValue, "%d", Min(cpu_count(), 7));


  o = option_with_name("Minimum Split Depth");
  assert(o != NULL);
  if(cpu_count() > 4) {
    sprintf(o->defaultValue, "%d", 6);
    sprintf(o->defaultValue, "%d", 6);
  }
}
