gt_reads2twobit_delete_sequences(GtReads2Twobit *r2t, GtBitsequence *list)
{
  GtTwobitencoding outputoffset = 0, *outputbuffer;
  unsigned long libnum, seqnum, output_seqnum,
                noflibs = gt_array_size(r2t->collection),
                deleted_sequences = 0, deleted_chars = 0, output_startpos = 0;
  for (libnum = 0; libnum < noflibs; libnum++)
  {
    GtReadsLibraryInfo *rli = gt_array_get(r2t->collection, libnum);
    if (rli->nofseqs > 0)
    {
      unsigned long deleted_sequences_in_lib = 0, deleted_chars_in_lib = 0,
                    last_seqnum = rli->first_seqnum + rli->nofseqs - 1UL;
      if (rli->filename2 != NULL)
        gt_reads2twobit_handle_deleted_mates(r2t, rli, list);
      for (seqnum = rli->first_seqnum; seqnum <= last_seqnum; seqnum++)
      {
        if (!GT_ISIBITSET(list, seqnum))
        {
          if (deleted_sequences > 0)
          {
            gt_assert(seqnum >= deleted_sequences);
            output_seqnum = seqnum - deleted_sequences;
            output_startpos = (r2t->seqlen_eqlen > 0)
              ? r2t->seqlen_eqlen * output_seqnum
              : ((output_seqnum == 0) ? 0 :
              r2t->seppos[output_seqnum - 1UL] + 1UL);
            outputbuffer = r2t->twobitencoding +
              GT_DIVBYUNITSIN2BITENC(output_startpos);
            outputoffset = (GtTwobitencoding)
              GT_MODBYUNITSIN2BITENC(output_startpos);
            (void)gt_reads2twobit_write_encoded(r2t, seqnum, outputbuffer,
                outputoffset, &outputoffset);
            if (r2t->seqlen_eqlen == 0)
            {
              unsigned long seqlen;
              gt_assert(seqnum > 0);
              seqlen = r2t->seppos[seqnum] - r2t->seppos[seqnum - 1UL];
              gt_assert(seqlen <= r2t->seqlen_max);
              gt_assert(output_startpos + seqlen <= r2t->total_seqlength);
              r2t->seppos[output_seqnum] = output_startpos + seqlen - 1UL;
            }
          }
        }
        else
        {
          deleted_chars_in_lib +=
            gt_reads2twobit_subtract_from_chardistri(r2t, seqnum);
          deleted_sequences++;
          deleted_sequences_in_lib++;
        }
      }
      deleted_chars += deleted_chars_in_lib;
      gt_assert(deleted_sequences_in_lib <= rli->nofseqs);
      if (rli->filename2 != NULL)
        gt_assert(deleted_sequences_in_lib % 2 == 0);
      rli->nofseqs -= deleted_sequences_in_lib;
      gt_assert(deleted_chars_in_lib <= rli->total_seqlength);
      rli->total_seqlength -= deleted_chars_in_lib;
    }
  }
  gt_assert(deleted_sequences <= r2t->nofseqs);
  r2t->nofseqs -= deleted_sequences;
  gt_assert(deleted_chars <= r2t->total_seqlength);
  r2t->total_seqlength -= deleted_chars;
  if (deleted_sequences > 0)
  {
    r2t->twobitencoding = gt_realloc(r2t->twobitencoding,
        sizeof (*r2t->twobitencoding) *
        (GT_DIVBYUNITSIN2BITENC(r2t->total_seqlength) + 2UL));
  }
}
