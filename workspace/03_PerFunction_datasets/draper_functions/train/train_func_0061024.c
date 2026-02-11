free_pr_header (PR *pr)
{
  int i;

  for (i = 0; i < NUM_HEADER_ITEMS; i++)
    {
      if (pr->private->header[i] != NULL)
	{
	  free (pr->private->header[i]);
	  pr->private->header[i] = NULL;
	}
    }
}
