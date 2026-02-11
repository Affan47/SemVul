a2a_sched_linear(int rank, int p, MPI_Aint sndext, MPI_Aint rcvext, NBC_Schedule* schedule, void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) {
  int res, r;
  char *rbuf, *sbuf;

  res = NBC_OK;

  for(r=0;r<p;r++) {

    if (r == rank) { continue; }
    rbuf = ((char *) recvbuf) + (r*recvcount*rcvext);
    res = NBC_Sched_recv(rbuf, false, recvcount, recvtype, r, schedule);
    if (NBC_OK != res) { printf("Error in NBC_Sched_recv() (%i)\n", res); return res; }
    sbuf = ((char *) sendbuf) + (r*sendcount*sndext);
    res = NBC_Sched_send(sbuf, false, sendcount, sendtype, r, schedule);
    if (NBC_OK != res) { printf("Error in NBC_Sched_send() (%i)\n", res); return res; }
  }

  return res;
}
