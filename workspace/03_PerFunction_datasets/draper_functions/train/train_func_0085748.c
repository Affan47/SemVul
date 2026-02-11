to_string(format_type type) const
{


  switch(type)
    {
    case format_hour_min_sec:
      {
	return "";
      }
    case format_min_sec:
      {
	return "";
      }
    case format_seconds: { return kvu_numtostr(seconds(), 6); }
    case format_samples: { return kvu_numtostr(samples_rep); }

    default: { }
    }

  return "";
}
