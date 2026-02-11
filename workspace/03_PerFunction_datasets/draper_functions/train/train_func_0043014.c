adns__parse_domain_more(findlabel_state *fls, adns_state ads,
				    adns_query qu, vbuf *vb,
				    parsedomain_flags flags,
				    const byte *dgram) {
  int lablen, labstart, i, ch, first;
  adns_status st;

  first= 1;
  for (;;) {
    st= adns__findlabel_next(fls,&lablen,&labstart);
    if (st) return st;
    if (lablen<0) { vb->used=0; return adns_s_ok; }
    if (!lablen) break;
    if (first) {
      first= 0;
    } else {
      if (!adns__vbuf_append(vb,".",1)) return adns_s_nomemory;
    }
    if (flags & pdf_quoteok) {
      if (!vbuf__append_quoted1035(vb,dgram+labstart,lablen))
	return adns_s_nomemory;
    } else {
      ch= dgram[labstart];
      if (!ctype_alpha(ch) && !ctype_digit(ch))
	return adns_s_answerdomaininvalid;
      for (i= labstart+1; i<labstart+lablen; i++) {
	ch= dgram[i];
	if (ch != '-' && !ctype_alpha(ch) && !ctype_digit(ch))
	  return adns_s_answerdomaininvalid;
      }
      if (!adns__vbuf_append(vb,dgram+labstart,lablen))
	return adns_s_nomemory;
    }
  }
  if (!adns__vbuf_append(vb,"",1)) return adns_s_nomemory;
  return adns_s_ok;
}
