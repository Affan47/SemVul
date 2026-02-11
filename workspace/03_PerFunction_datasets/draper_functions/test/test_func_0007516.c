do_gline(struct Client *cptr, struct Client *sptr, struct Gline *gline)
{
  struct Client *acptr;
  int fd, retval = 0, tval;

  if (GlineIsBadChan(gline))
    return 0;
  if (!GlineIsActive(gline))
    return 0;

  for (fd = HighestFd; fd >= 0; --fd) {


    if ((acptr = LocalClientArray[fd])) {
      if (!cli_user(acptr))
	continue;

      if (GlineIsRealName(gline)) {
	Debug((DEBUG_DEBUG,"Realname Gline: %s %s",(cli_info(acptr)),
					gline->gl_user+2));
        if (match(gline->gl_user+2, cli_info(acptr)) != 0)
            continue;
        Debug((DEBUG_DEBUG,"Matched!"));
      } else {
        if (cli_user(acptr)->username &&
            match(gline->gl_user, (cli_user(acptr))->username) != 0)
          continue;

        if (GlineIsIpMask(gline)) {
          if (!ipmask_check(&cli_ip(acptr), &gline->gl_addr, gline->gl_bits))
            continue;
        }
        else {
          if (match(gline->gl_host, cli_sockhost(acptr)) != 0)
            continue;
        }
      }


      send_reply(acptr, SND_EXPLICIT | ERR_YOUREBANNEDCREEP, ":%s",
      	   gline->gl_reason);


      sendto_opmask_butone(0, SNO_GLINE, "G-line active for %s",
                           get_client_name(acptr, SHOW_IP));


      if ((tval = exit_client_msg(cptr, acptr, &me, "G-lined (%s)",
          gline->gl_reason)))
        retval = tval;
    }
  }
  return retval;
}
