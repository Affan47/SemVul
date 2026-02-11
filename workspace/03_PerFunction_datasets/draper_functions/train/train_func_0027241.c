AllocateThreadViewDataSet(const MagickFreeFunc destructor,
                          const Image *image,
                          ExceptionInfo *exception)
{
  ThreadViewDataSet
    *data_set;

  MagickPassFail
    status=MagickPass;

  data_set=MagickAllocateMemory(ThreadViewDataSet *,sizeof(ThreadViewDataSet));
  if (data_set == (ThreadViewDataSet *) NULL)
    MagickFatalError3(ResourceLimitFatalError,MemoryAllocationFailed,
                      UnableToAllocateCacheView);
  data_set->destructor=destructor;
  data_set->nviews=omp_get_max_threads();
  data_set->view_data=MagickAllocateArray(void *,data_set->nviews,sizeof(void *));
  if (data_set->view_data == (void *) NULL)
    {
      ThrowException(exception,ResourceLimitError,MemoryAllocationFailed,
                     image->filename);
      status=MagickFail;
    }

  if (data_set->view_data != (void *) NULL)
    (void) memset(data_set->view_data,0,data_set->nviews*sizeof(void *));

  if (status == MagickFail)
    {
      DestroyThreadViewDataSet(data_set);
      data_set=(ThreadViewDataSet *) NULL;
    }

  return data_set;
}
