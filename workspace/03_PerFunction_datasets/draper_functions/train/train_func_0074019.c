edfwrite_digital_samples(int handle, int *buf)
{
  int  i, p,
       error,
       sf,
       digmax,
       digmin,
       edfsignal,
       value;

  FILE *file;

  struct edfhdrblock *hdr;


  if(handle<0)
  {
    return(-1);
  }

  if(handle>=EDFLIB_MAXFILES)
  {
    return(-1);
  }

  if(hdrlist[handle]==NULL)
  {
    return(-1);
  }

  if(!(hdrlist[handle]->writemode))
  {
    return(-1);
  }

  if(hdrlist[handle]->edfsignals == 0)
  {
    return(-1);
  }

  hdr = hdrlist[handle];

  file = hdr->file_hdl;

  edfsignal = hdr->signal_write_sequence_pos;

  if(!hdr->datarecords)
  {
    if(!edfsignal)
    {
      error = edflib_write_edf_header(hdr);

      if(error)
      {
        return(error);
      }
    }
  }

  sf = hdr->edfparam[edfsignal].smp_per_record;

  digmax = hdr->edfparam[edfsignal].dig_max;

  digmin = hdr->edfparam[edfsignal].dig_min;

  for(i=0; i<sf; i++)
  {
    value = buf[i];

    if(value>digmax)
    {
      value = digmax;
    }

    if(value<digmin)
    {
      value = digmin;
    }

    fputc((value)&0xff, file);

    if(fputc((value>>8)&0xff, file)==EOF)
    {
      return(-1);
    }

    if(hdr->bdf)
    {
      fputc((value>>16)&0xff, file);
    }
  }

  hdr->signal_write_sequence_pos++;

  if(hdr->signal_write_sequence_pos == hdr->edfsignals)
  {
    hdr->signal_write_sequence_pos = 0;

    p = edflib_fprint_ll_number_nonlocalized(file, (hdr->datarecords * hdr->long_data_record_duration) / EDFLIB_TIME_DIMENSION, 0, 1);
    if(hdr->long_data_record_duration % EDFLIB_TIME_DIMENSION)
    {
      fputc('.', file);
      p++;
      p += edflib_fprint_ll_number_nonlocalized(file, (hdr->datarecords * hdr->long_data_record_duration) % EDFLIB_TIME_DIMENSION, 7, 0);
    }
    fputc(20, file);
    fputc(20, file);
    p += 2;
    for(; p<hdr->total_annot_bytes; p++)
    {
      fputc(0, file);
    }

    hdr->datarecords++;

    fflush(file);
  }

  return(0);
}
