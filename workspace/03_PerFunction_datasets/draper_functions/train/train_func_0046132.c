fragment_ttl_reap (struct fragment_master *f)
{
  int i;
  for (i = 0; i < N_FRAG_BUF; ++i)
    {
      struct fragment *frag = &f->incoming.fragments[i];
      if (frag->defined && frag->timestamp + FRAG_TTL_SEC <= now)
	{
	  msg (D_FRAG_ERRORS, "FRAG TTL expired i=%d", i);
	  frag->defined = false;
	}
    }
}
