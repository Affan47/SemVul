pa_rp(const parseinfo *pai, int cbyte,
			 int max, void *datap) {
  adns_rr_strpair *rrp= datap;
  adns_status st;

  st= pap_mailbox(pai, &cbyte, max, &rrp->array[0]);
  if (st) return st;

  st= pap_domain(pai, &cbyte, max, &rrp->array[1], pdf_quoteok);
  if (st) return st;

  if (cbyte != max) return adns_s_invaliddata;
  return adns_s_ok;
}
