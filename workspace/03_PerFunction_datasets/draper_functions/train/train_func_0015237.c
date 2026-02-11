check_timeouts ()
{
  int nhop;
  int need_reply = 0;
  int no_reply = 0;
  int last_return = 0;
  unsigned int tseq;

  tseq = 0;

  gettimeofday (&now, NULL);
  if (timediff_ms (ts_last_sent, now) < scatter_ms)
    return;

  for (nhop = ttl_min; nhop < hop_info_length; nhop++) {
    if (!hop_info[nhop].num_sent) {
      if (noisy) printf("Sending FIRST PACKET for hop %d\n", nhop);
      send_hop(nhop);
      return;
    }
  }

  for (nhop = ttl_min; nhop < hop_info_length; nhop++) {
    if (hop_info[nhop].num_sent <= retry_max && !hop_info[nhop].ts_last_recv.tv_sec) {
      if (noisy == 2) printf("No reply on TTL %d; ", nhop);
      if (timediff_ms (hop_info[nhop].ts_last_sent, now) >= timeout_ms) {


	if (hop_info[nhop].num_sent < retry_max) {
	  if (noisy == 2) printf("timed out, resending\n");
	  send_hop(nhop);
	  return;
	} else {
	  if (!smart || hop_state_up(nhop)) {
	    if (noisy == 2) printf("timed out, no reply\n");
	    no_reply++;
	  }
	}
      } else {
	if (noisy == 2) printf("not timed out\n");
	need_reply++;
      }
    } else {
      last_return = nhop;
    }
  }

  if (noisy == 2) {
    printf ("hop_info_length %d, last_return %d\n", hop_info_length, last_return);
    printf ("no_reply %d, ahead_limit %d\n", no_reply, ahead_limit);
    printf ("num_hops %d\n", num_hops);
    printf ("need_reply %d\n", need_reply);
  }
  if (no_reply >= ahead_limit) {
    if ((last_return + 3) * 2 < hop_info_length) {
      printf("\n\nLFT can\'t seem to round-trip.  Local packet filter in the way?");
      if (noisy == 2) printf("Will finish ONE\n");
      finish ();
    }


  }

  if ((!num_hops || hop_info_length < num_hops || need_reply) && hop_info_length < ttl_limit) {
    if (noisy == 2) printf("I still have unanswered hops.\n");
    if (need_reply >= ahead_limit) {
      if (noisy == 2) printf("\tI\'m too far ahead, recycling.\n");
      return;
    }

    if (num_hops > 0 && hop_info_length >= num_hops) {
      if (noisy == 2) printf("I have blanks to fill -  RETURN \n");
      return;

    }

    nhop = hop_info_length++;
    send_hop(nhop);
  } else {
    if (noisy) printf("Everyone responded.  Moving on...\n");
    for (nhop = ttl_min; nhop < hop_info_length; nhop++) {
      if (hop_info[nhop].num_sent < retry_min && hop_info[nhop].num_sent <= retry_max ) {
	send_hop(nhop);
	return;
      }
    }

    if (noisy) printf("Will finish TWO\n");
    finish ();
  }
}
