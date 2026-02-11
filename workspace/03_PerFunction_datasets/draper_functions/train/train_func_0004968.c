sample_format(void) const
{
  Sample_format format (sfmt_none);
  try {
    format = string_to_sample_format(format_string());
  }
  catch(...) {}
  return format;
}
