free_scc (ddg_scc_ptr scc)
{
  if (!scc)
    return;

  sbitmap_free (scc->nodes);
  if (scc->num_backarcs > 0)
    free (scc->backarcs);
  free (scc);
}
