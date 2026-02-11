s48_extract_socket_type(s48_call_t call, s48_ref_t sch_socktype)
{
  long socktype_val = s48_extract_long_2(call, sch_socktype);
  if (socktype_val > 100)
    return socktype_val - 100;
  else
    switch (socktype_val)
      {
      case 0:
	return SOCK_STREAM;
      case 1:
	return SOCK_DGRAM;
      }
}
