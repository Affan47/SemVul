getWorkerAverages() {
  double avg_response_time = 0;
  int job_count = 0;

  map<long,int>::iterator it;

  list<Worker *>::iterator worker;
  for (worker = workers.begin(); worker != workers.end(); ++worker) {
    map<long,int> times = (*worker)->getCompletionTimes(config->sliding_window*1000);

    if( (*worker)->getState() == IDLE ||
        (*worker)->getState() == COMPUTING ||
        (*worker)->getState() == SWAPPING  ) {
      for (it = times.begin();
           it != times.end(); ++it) {
        if ((*it).first <= (currentTime - (config->sliding_window*1000))) {
          avg_response_time += (*it).second;
          job_count++;
        }
      }
    }
  }

  avg_response_time = avg_response_time/job_count;
  return avg_response_time;
}
