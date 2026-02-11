hist_read_rec (FILE * ifp, const char *filename)
{
  bfd_vma lowpc, highpc;
  histogram n_record;
  histogram *record, *existing_record;
  unsigned i;


  read_histogram_header (&n_record, ifp, filename, num_histograms == 0);

  existing_record = find_histogram (n_record.lowpc, n_record.highpc);
  if (existing_record)
    {
      record = existing_record;
    }
  else
    {


      lowpc = n_record.lowpc;
      highpc = n_record.highpc;
      hist_clip_symbol_address (&lowpc, &highpc);
      if (lowpc != highpc)
	{
	  fprintf (stderr,
		   _("%s: overlapping histogram records\n"),
		   whoami);
	  done (1);
	}


      histograms = (struct histogram *)
          xrealloc (histograms, sizeof (histogram) * (num_histograms + 1));
      memcpy (histograms + num_histograms,
	      &n_record, sizeof (histogram));
      record = &histograms[num_histograms];
      ++num_histograms;

      record->sample = (int *) xmalloc (record->num_bins
					* sizeof (record->sample[0]));
      memset (record->sample, 0, record->num_bins * sizeof (record->sample[0]));
    }


  DBG (SAMPLEDEBUG,
       printf ("[hist_read_rec] n_lowpc 0x%lx n_highpc 0x%lx ncnt %u\n",
	       (unsigned long) record->lowpc, (unsigned long) record->highpc,
               record->num_bins));

  for (i = 0; i < record->num_bins; ++i)
    {
      UNIT count;
      if (fread (&count[0], sizeof (count), 1, ifp) != 1)
	{
	  fprintf (stderr,
		  _("%s: %s: unexpected EOF after reading %u of %u samples\n"),
		   whoami, filename, i, record->num_bins);
	  done (1);
	}
      record->sample[i] += bfd_get_16 (core_bfd, (bfd_byte *) & count[0]);
      DBG (SAMPLEDEBUG,
	   printf ("[hist_read_rec] 0x%lx: %u\n",
		   (unsigned long) (record->lowpc
                                    + i * (record->highpc - record->lowpc)
                                    / record->num_bins),
		   record->sample[i]));
    }
}
