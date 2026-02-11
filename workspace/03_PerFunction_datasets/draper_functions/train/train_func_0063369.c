dns_event_success(struct resolve *rp, int type)
{
  if (!rp)
    return;

  if (type == T_PTR) {
    debug2("DNS resolved %s to %s", iptostr(rp->ip), rp->hostn);
    call_hostbyip(ntohl(rp->ip), rp->hostn, 1);
  } else if (type == T_A) {
    debug2("DNS resolved %s to %s", rp->hostn, iptostr(rp->ip));
    call_ipbyhost(rp->hostn, ntohl(rp->ip), 1);
  }
}
