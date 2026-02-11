ipv4_scan(const char* start, ipv4addr* addr)
{
  const char* s;
  if ((s = parse_part(start, &addr->addr[0])) == 0) return 0;
  if (*s != '.' && addr->addr[0] == 0) {

    memset(addr, 0, sizeof *addr);
    return s;
  }
  if ((s = parse_part(s+1, &addr->addr[1])) == 0 || *s != '.') return 0;
  if ((s = parse_part(s+1, &addr->addr[2])) == 0 || *s != '.') return 0;
  if ((s = parse_part(s+1, &addr->addr[3])) == 0) return 0;
  return s;
}
