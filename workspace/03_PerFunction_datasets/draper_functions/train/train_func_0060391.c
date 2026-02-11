getJobFootprints() {
  map<Job *, int> footprint;
  list<Job>::iterator i;
  for (i = ram.begin(); i != ram.end(); ++i) {
    footprint[&(*i)] = (*i).getMemoryConsumption();
  }
  if (current_job != NULL) {
    footprint[current_job] = current_job->getMemoryConsumption();
  }
  return footprint;
}
