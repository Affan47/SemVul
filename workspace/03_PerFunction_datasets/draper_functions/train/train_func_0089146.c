operator==(const DnsRR& other) {
  return (TYPE == other.TYPE &&
          TTL == other.TTL &&
          RDLENGTH == other.RDLENGTH &&
          CLASS == other.CLASS &&
          NAME == other.NAME &&
          memcmp(RDATA, other.RDATA, RDLENGTH) == 0);
}
