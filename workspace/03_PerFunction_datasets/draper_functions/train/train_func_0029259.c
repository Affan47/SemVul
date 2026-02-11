setcallback(int slot,char **argv)
{
  lcp_wantoptions[slot].neg_callback = 1;
  if (lcp_wantoptions[slot].cbopt.type != CB_AUTH) {
    lcp_wantoptions[slot].cbopt.message = strdup(*argv);
    if (lcp_wantoptions[slot].cbopt.message != 0) {
      lcp_wantoptions[slot].cbopt.mlen =
	strlen(lcp_wantoptions[slot].cbopt.message);
      if (!lcp_wantoptions[slot].cbopt.mlen)
	lcp_wantoptions[slot].cbopt.message = 0;
    } else {
      lcp_wantoptions[slot].cbopt.mlen = 0;
    }
  } else {
      lcp_wantoptions[slot].cbopt.mlen = 0;
      lcp_wantoptions[slot].cbopt.message = 0;
  }

  if (lcp_wantoptions[slot].cbopt.neg_cbcp)
    cbcp_protent.enabled_flag = 1;
  return 1;
}
