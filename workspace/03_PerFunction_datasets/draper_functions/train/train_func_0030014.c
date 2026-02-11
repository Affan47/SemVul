logRunningAverage() {
  int offline_workers_count = 0;
  int idle_workers_count = 0;
  int computing_workers_count = 0;
  int queued_jobs = 0;
  double avg_response_time = 0;
  float cost_so_far = 0;

  list<Worker *>::iterator worker;
  for (worker = workers.begin(); worker != workers.end(); ++worker) {
    if ((*worker)->ping()) {
      queued_jobs += (*worker)->getQueuedJobs();
      if ((*worker)->getState() == COMPUTING)
        queued_jobs++;
    }

    if( (*worker)->getState() == OFFLINE  ) {
      offline_workers_count++;

    }
    if( (*worker)->getState() == IDLE  ) {
      idle_workers_count++;
      cost_so_far += (*worker)->getTotalCost();
    }
    if( (*worker)->getState() == COMPUTING ||
        (*worker)->getState() == SWAPPING  ) {
      computing_workers_count++;
      cost_so_far += (*worker)->getTotalCost();
    }
  }

  list<double>::iterator it;
  for (it = slidingWindow.begin(); it != slidingWindow.end(); ++it) {
    avg_response_time += *it;
  }
  avg_response_time = avg_response_time/(int)slidingWindow.size();

  logger->workerAverage(avg_response_time/1000,
                        cost_so_far,
                        offline_workers_count,
                        idle_workers_count,
                        computing_workers_count,
                        queued_jobs);

  csv_file<<currentTime<<","<<avg_response_time<<","<<cost_so_far<<","<<idle_workers_count+computing_workers_count<<endl;
}
