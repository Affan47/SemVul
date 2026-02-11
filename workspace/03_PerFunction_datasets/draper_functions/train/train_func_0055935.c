gst_ogg_mux_compare_pads (GstOggMux * ogg_mux, GstOggPadData * first,
    GstOggPadData * second)
{
  guint64 firsttime, secondtime;


  if (first == NULL)
    return 1;
  if (second == NULL)
    return -1;


  firsttime = GST_BUFFER_TIMESTAMP (first->buffer);
  if (firsttime == GST_CLOCK_TIME_NONE)
    return -1;


  secondtime = GST_BUFFER_TIMESTAMP (second->buffer);
  if (secondtime == GST_CLOCK_TIME_NONE)
    return 1;


  if (secondtime < firsttime)
    return 1;

  else if (secondtime > firsttime)
    return -1;
  else {


    if (second->pageno < first->pageno)
      return 1;
    else if (second->pageno > first->pageno)
      return -1;
  }


  return 0;
}
