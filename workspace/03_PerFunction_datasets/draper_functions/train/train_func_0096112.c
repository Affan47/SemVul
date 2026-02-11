sort_realtmp(GtArray * realfrom,
                         GtArray * realto,
                         GtArray * real_fromtmp, GtArray * real_totmp)
{
  unsigned long index_outer,
    index_inner,
    max_value = 0,
    from,
    to,
    from_tmp = 0,
    to_tmp = 0;


  for (index_outer = 0; index_outer < gt_array_size(real_fromtmp);
       index_outer++)
  {

    for (index_inner = 0; index_inner < gt_array_size(real_fromtmp);
         index_inner++)
    {
      from = *(unsigned long *) gt_array_get(real_fromtmp, index_inner);
      to = *(unsigned long *) gt_array_get(real_totmp, index_inner);


      if (gt_array_size(realfrom) > 0)
      {


        if ((from > from_tmp) && (from < max_value))
        {
          from_tmp = from;
          to_tmp = to;
        }
      }

      else
      {

        if (from > from_tmp)
        {
          from_tmp = from;
          to_tmp = to;
        }
      }
    }

    gt_array_add(realfrom, from_tmp);
    gt_array_add(realto, to_tmp);


    max_value = from_tmp;
    from_tmp = 0;
    to_tmp = 0;
  }
}
