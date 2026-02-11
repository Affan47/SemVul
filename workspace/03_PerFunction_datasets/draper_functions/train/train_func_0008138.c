extract_ip_protocol(s48_call_t call, s48_ref_t sch_protocol)
{
  long ip = s48_extract_long_2(call, sch_protocol);
  if (ip > 100)
    return ip - 100;
  else
    switch (ip)
      {
      case 0:
	return IPPROTO_IP;
      case 1:
	return IPPROTO_IPV6;
      case 2:
	return IPPROTO_ICMP;
      case 3:
	return IPPROTO_RAW;
      case 4:
	return IPPROTO_TCP;
      case 5:
	return IPPROTO_UDP;
    }
}
