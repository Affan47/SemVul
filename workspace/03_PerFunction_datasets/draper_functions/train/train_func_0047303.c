gt_kmercodeiterator_filetab_next(const GtKmercode **kmercodeptr,
                                     GtKmercodeiterator *kmercodeiterator,
                                     GtError *err)
{
  if (!kmercodeiterator->inputexhausted)
  {
    if (kmercodeiterator->hasprocessedfirst)
    {
      GtUchar charcode;
      int retval;

      retval = gt_sequence_buffer_next(kmercodeiterator->fb,&charcode,err);
      if (retval < 0)
      {
        *kmercodeptr = NULL;
        return -1;
      }
      if (retval != 0)
      {
        shiftrightwithchar(kmercodeiterator->spwp,charcode);
        kmerstream_newcode(&kmercodeiterator->kmercode, kmercodeiterator->spwp);
        kmercodeiterator->currentposition++,
        *kmercodeptr = &kmercodeiterator->kmercode;
        return 0;
      }
      kmercodeiterator->inputexhausted = true;
      kmercodeiterator->totallength = kmercodeiterator->currentposition;
    } else
    {
      kmerstream_newcode(&kmercodeiterator->kmercode, kmercodeiterator->spwp);
      kmercodeiterator->hasprocessedfirst = true;
      *kmercodeptr = &kmercodeiterator->kmercode;
      return 0;
    }
  }
  if (kmercodeiterator->currentposition < kmercodeiterator->totallength +
                                          kmercodeiterator->spwp->kmersize)
  {
    shiftrightwithchar(kmercodeiterator->spwp,(GtUchar) WILDCARD);
    kmerstream_newcode(&kmercodeiterator->kmercode, kmercodeiterator->spwp);
    kmercodeiterator->currentposition++,
    *kmercodeptr = &kmercodeiterator->kmercode;
  } else
  {
    *kmercodeptr = NULL;
  }
  return 0;
}
