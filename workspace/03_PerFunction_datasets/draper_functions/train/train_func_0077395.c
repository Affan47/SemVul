getAverageResponseTime() {
  double avg = 1;
  int number_of_jobs = 0;

  list<Job>::iterator job;
  for (job = jobs.begin(); job != jobs.end(); ++job) {
    avg += (currentTime - (*job).getStartedTime());
    number_of_jobs++;
  }

  for (job = ram.begin(); job != ram.end(); ++job) {
    avg += (currentTime - (*job).getStartedTime());
    number_of_jobs++;
  }

  if (current_job != NULL) {
    avg += (currentTime - current_job->getStartedTime());
    number_of_jobs++;
  }

  return (number_of_jobs > 0 ? avg/number_of_jobs : avg);
}
