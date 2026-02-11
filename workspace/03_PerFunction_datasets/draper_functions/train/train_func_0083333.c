adns_submit_reverse(adns_state ads,
			const struct sockaddr *addr,
			adns_rrtype type,
			adns_queryflags flags,
			void *context,
			adns_query *query_r) {
  if (type != adns_r_ptr && type != adns_r_ptr_raw) return EINVAL;
  return adns_submit_reverse_any(ads,addr,"in-addr.arpa",
				 type,flags,context,query_r);
}
