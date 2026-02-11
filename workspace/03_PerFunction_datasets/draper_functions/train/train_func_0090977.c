set(format_type type, const std::string& time)
{
  switch(type)
    {

    case format_hour_min_sec: { DBC_CHECK(false); break; }

    case format_min_sec: { DBC_CHECK(false); break; }
    case format_seconds:
      {
	double seconds = atof(time.c_str());
	set_seconds(seconds);
	break;
      }
    case format_samples:
      {
	samples_rep = atol(time.c_str());
	break;
      }
    default: { }
    }
}
