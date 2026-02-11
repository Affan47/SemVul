fd_dump(struct Client *source_p)
{
  int i;
  fde_t *F;

  for (i = 0; i < FD_HASH_SIZE; i++)
    for (F = fd_hash[i]; F != NULL; F = F->hnext)
      sendto_one(source_p, ":%s %d %s :fd %-5d desc '%s'",
                 me.name, RPL_STATSDEBUG, source_p->name,
                 F->fd, F->desc);
}
