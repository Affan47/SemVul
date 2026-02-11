PixelIterateMonoRead(PixelIteratorMonoReadCallback call_back,
                     const PixelIteratorOptions *options,
                     const char *description,
                     void *mutable_data,
                     const void *immutable_data,
                     const long x,
                     const long y,
                     const unsigned long columns,
                     const unsigned long rows,
                     const Image *image,
                     ExceptionInfo *exception)
{
  MagickPassFail
    status = MagickPass;

  register long
    row;

  unsigned long
    row_count=0;

#if defined(HAVE_OPENMP)
  int num_threads=GetRegionThreads(options,GetPixelCacheInCore(image),columns,rows);
#else
  (void) options;
#endif

#if defined(HAVE_OPENMP)
#  if defined(TUNE_OPENMP)
#    pragma omp parallel for if(num_threads > 1) num_threads(num_threads) schedule(runtime) shared(row_count, status)
#  else
#    pragma omp parallel for if(num_threads > 1) num_threads(num_threads) schedule(static,1) shared(row_count, status)
#  endif
#endif
  for (row=y; row < (long) (y+rows); row++)
    {
      MagickPassFail
        thread_status;

      const PixelPacket
        * restrict pixels;

      const IndexPacket
        * restrict indexes;

#if defined(HAVE_OPENMP)
#  pragma omp critical (GM_PixelIterateMonoRead)
#endif
      thread_status=status;
      if (thread_status == MagickFail)
	continue;

      pixels=AcquireImagePixels(image,x, row, columns, 1, exception);
      if (!pixels)
        thread_status=MagickFail;
      indexes=AccessImmutableIndexes(image);

      if (thread_status != MagickFail)
        thread_status=(call_back)(mutable_data,immutable_data,image,pixels,indexes,columns,exception);

#if defined(HAVE_OPENMP)
#  pragma omp critical (GM_PixelIterateMonoRead)
#endif
      {
        row_count++;
        if (QuantumTick(row_count,rows))
          if (!MagickMonitorFormatted(row_count,rows,exception,
                                      description,image->filename))
            thread_status=MagickFail;

        if (thread_status == MagickFail)
          status=MagickFail;
      }
    }

  return (status);
}
