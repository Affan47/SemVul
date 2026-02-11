allred_sched_linear(int rank, int rsize, void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype,
				      MPI_Op op, int ext, int size, NBC_Schedule *schedule, NBC_Handle *handle) {
  int res, rpeer;

  if(count == 0) return NBC_OK;


  res = NBC_Sched_send (sendbuf, false, count, datatype, 0, schedule);
  if (NBC_OK != res) { printf("Error in NBC_Sched_send() (%i)\n", res); return res; }

  res = NBC_Sched_recv (recvbuf, false, count, datatype, 0, schedule);
  if (NBC_OK != res) { printf("Error in NBC_Sched_recv() (%i)\n", res); return res; }

  if (0 == rank) {

    res = NBC_Sched_barrier (schedule);
    if (NBC_OK != res) { printf("Error in NBC_Sched_barrier() (%i)\n", res); return res; }


    for (rpeer = 1 ; rpeer < rsize ; ++rpeer) {
      res = NBC_Sched_recv (0, true, count, datatype, rpeer, schedule);
      if (NBC_OK != res) { printf("Error in NBC_Sched_recv() (%i)\n", res); return res; }

      res = NBC_Sched_barrier(schedule);
      if (NBC_OK != res) { printf("Error in NBC_Sched_barrier() (%i)\n", res); return res; }

      res = NBC_Sched_op (recvbuf, false, 0, true, recvbuf, false, count, datatype, op, schedule);
      if (NBC_OK != res) { printf("Error in NBC_Sched_op() (%i)\n", res); return res; }

      res = NBC_Sched_barrier(schedule);
      if (NBC_OK != res) { printf("Error in NBC_Sched_barrier() (%i)\n", res); return res; }
    }


    res = NBC_Sched_recv (0, true, count, datatype, 0, schedule);
    if (NBC_OK != res) { printf("Error in NBC_Sched_recv() (%i)\n", res); return res; }

    res = NBC_Sched_send (recvbuf, false, count, datatype, 0, schedule);
    if (NBC_OK != res) { printf("Error in NBC_Sched_send() (%i)\n", res); return res; }


    res = NBC_Sched_barrier(schedule);
    if (NBC_OK != res) { printf("Error in NBC_Sched_barrier() (%i)\n", res); return res; }


    for (rpeer = 1 ; rpeer < rsize ; ++rpeer) {
      res = NBC_Sched_send (0, true, count, datatype, rpeer, schedule);
      if (NBC_OK != res) { printf("Error in NBC_Sched_send() (%i)\n", res); return res; }
    }
  }

  return NBC_OK;
}
