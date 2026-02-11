addr_eq(const ioa_addr* a1, const ioa_addr *a2) {

  if(!a1) return (!a2);
  else if(!a2) return (!a1);

  if(a1->ss.sa_family == a2->ss.sa_family) {
    if(a1->ss.sa_family == AF_INET && a1->s4.sin_port == a2->s4.sin_port) {
      if((int)a1->s4.sin_addr.s_addr == (int)a2->s4.sin_addr.s_addr) {
	return 1;
      }
    } else if(a1->ss.sa_family == AF_INET6 && a1->s6.sin6_port == a2->s6.sin6_port) {
      const u64bits *p1=(const u64bits *)(&(a1->s6.sin6_addr));
      const u64bits *p2=(const u64bits *)(&(a2->s6.sin6_addr));
      if(p1[0]==p2[0] && p1[1]==p2[1]) {
	return 1;
      }
    }
  }

  return 0;
}
