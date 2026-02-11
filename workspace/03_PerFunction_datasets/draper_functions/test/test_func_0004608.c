free_file_system_list(struct mount_entry *p)
{
  while (p)
    {
      struct mount_entry *pnext = p->me_next;

      free(p->me_devname);
      free(p->me_mountdir);

      if(p->me_type_malloced)
	free(p->me_type);
      p->me_next = NULL;
      free(p);
      p = pnext;
    }
}
