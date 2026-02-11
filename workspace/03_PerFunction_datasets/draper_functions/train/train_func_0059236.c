df_sort_and_compress_refs (VEC(df_ref,stack) **ref_vec)
{
  unsigned int count;
  unsigned int i;
  unsigned int dist = 0;

  count = VEC_length (df_ref, *ref_vec);


  if (count < 2)
    return;
  else if (count == 2)
    {
      df_ref r0 = VEC_index (df_ref, *ref_vec, 0);
      df_ref r1 = VEC_index (df_ref, *ref_vec, 1);
      if (df_ref_compare (&r0, &r1) > 0)
        df_swap_refs (ref_vec, 0, 1);
    }
  else
    {
      for (i = 0; i < count - 1; i++)
	{
	  df_ref r0 = VEC_index (df_ref, *ref_vec, i);
	  df_ref r1 = VEC_index (df_ref, *ref_vec, i + 1);
	  if (df_ref_compare (&r0, &r1) >= 0)
	    break;
	}


      if (i == count - 1)
        return;
      VEC_qsort (df_ref, *ref_vec, df_ref_compare);
    }

  for (i=0; i<count-dist; i++)
    {

      while (i + dist + 1 < count
	     && df_ref_equal_p (VEC_index (df_ref, *ref_vec, i),
				VEC_index (df_ref, *ref_vec, i + dist + 1)))
	{
	  df_free_ref (VEC_index (df_ref, *ref_vec, i + dist + 1));
	  dist++;
	}

      if (dist && i + dist + 1 < count)
	VEC_replace (df_ref, *ref_vec, i + 1,
		     VEC_index (df_ref, *ref_vec, i + dist + 1));
    }

  count -= dist;
  VEC_truncate (df_ref, *ref_vec, count);
}
