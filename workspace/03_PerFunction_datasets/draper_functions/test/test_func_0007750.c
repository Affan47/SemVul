vt_omp_fork2(uint32_t tid, uint32_t* ptid)
{
  GET_THREAD_ID(tid);

  *ptid = tid;

  vt_omp_fork(tid);
}
