xmit_id(struct interface *i)
{
  if (Verbose) {
    fprintf(stderr,"%s: TX: ID\n",i->port);
  }
  if (sendto(i->tsock,i->idbuf,i->idlen,
	     0,(struct sockaddr *)&i->tsa,i->tsa_size) < 0)
    perror(i->devname);
  i->i_flags &= ~I_NEED_ID;
  i->next_id = 0;
  ++i->stats.ids;
}
