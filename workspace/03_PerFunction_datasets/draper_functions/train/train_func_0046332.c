decompose_hangul (gunichar s, gunichar * r, gsize * result_len)
{
  gint SIndex = s - SBase;


  if (SIndex < 0 || SIndex >= SCount)
    {
      if (r)
	r[0] = s;
      *result_len = 1;
    }
  else
    {
      gunichar L = LBase + SIndex / NCount;
      gunichar V = VBase + (SIndex % NCount) / TCount;
      gunichar T = TBase + SIndex % TCount;

      if (r)
	{
	  r[0] = L;
	  r[1] = V;
	}

      if (T != TBase)
	{
	  if (r)
	    r[2] = T;
	  *result_len = 3;
	}
      else
	*result_len = 2;
    }
}
