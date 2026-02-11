linux_fifo_scheduler() {


  struct sched_param schedParam;
  schedParam.sched_priority = sched_get_priority_max(SCHED_FIFO);
  if (sched_setscheduler(0, SCHED_FIFO, &schedParam)) {
    int err = errno;
    if (err == EINVAL) {
      throw std::runtime_error(
          "The scheduling policy is not one of the recognized policies, param "
          "is NULL, or param does not make sense for the policy.\n");
    } else if (err == EPERM) {
      throw std::runtime_error(
          "The calling thread does not have appropriate privileges.\n");
    } else
      throw std::runtime_error("set scheduler fail");
  }
}
