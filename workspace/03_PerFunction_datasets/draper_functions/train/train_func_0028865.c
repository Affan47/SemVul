findrm(fd_struct *entry, fdque *que)
{
  fd_struct	**fp,
    *f;

  for (fp = &que->first; (f = *fp) != entry; fp = &f->next)
    if (f == NULL) {
      fprintf(stderr, "ERROR: findrm fd %d, status %d not on queue.\n",
	      entry->fd, entry->status);
      return;
    }
  rmque(fp, que);
}
