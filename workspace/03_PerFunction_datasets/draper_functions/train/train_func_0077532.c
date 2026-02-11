write_checkpoint(uint64_t p)
{
  FILE *fout;
  unsigned int i;
  uint64_t count, sum, checksum;

  if ((fout = fopen(checkpoint_filename,"w")) != NULL)
  {
    for (i = 0, count = cand_count, sum = cand_sum; i < num_threads; i++)
    {
      count += thread_data[i].count;
      sum += thread_data[i].sum;
    }

    checksum = pmin + p + count + sum;
    fprintf(fout,"pmin=%"PRIu64",p=%"PRIu64
        ",count=%"PRIu64",sum=0x%016"PRIx64",checksum=0x%016"PRIx64"\n",
        pmin,p,count,sum,checksum);

    app_write_checkpoint(fout);
    fclose(fout);
  }
}
