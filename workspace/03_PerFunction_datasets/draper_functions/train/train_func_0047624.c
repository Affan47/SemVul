vt_omp_parallel_begin2(uint32_t tid, uint32_t ptid)
{
  GET_THREAD_ID(tid);
#if (defined(VT_MT) || defined(VT_HYB))
  VTThrd_registerThread(ptid);
#endif
  vt_omp_parallel_begin(tid);
}
