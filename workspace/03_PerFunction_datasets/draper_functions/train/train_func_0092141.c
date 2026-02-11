loop_packet(struct ax_calls *calls,u_char *cp,int len)
{
  int n, flags;
  int j;
  struct interface *iface;
  struct callsign_list *cl;

  for (n = 0; n < calls->ax_next_digi; n++) {
    if (calls->ax_digi_call[n].ax25_call[ALEN]&REPEATED) {
      for (j = 0, iface = Intf; j < N_intf; j++, iface++) {
	if (ax25_cmp(&MYCALL(j),&calls->ax_digi_call[n]) == 0) {
	  if (Verbose)
	    fprintf(stderr,"loop_packet: found my call %s at digi_call[%d]\n",
		    ax25_ntoa_pretty(&calls->ax_digi_call[n]),n);
	  return 1;
	}
      }
    } else
      return 0;
  }
  return 0;
}
