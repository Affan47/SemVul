free_histograms (void)
{
  if (VALUE_HISTOGRAMS (cfun))
    {
      htab_traverse (VALUE_HISTOGRAMS (cfun), free_hist, NULL);
      htab_delete (VALUE_HISTOGRAMS (cfun));
      VALUE_HISTOGRAMS (cfun) = NULL;
    }
}
