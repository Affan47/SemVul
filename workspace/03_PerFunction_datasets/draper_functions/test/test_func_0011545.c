evd_web_selector_free_candidate (gpointer user_data)
{
  EvdWebSelectorCandidate *candidate = user_data;

  if (candidate->domain_pattern != NULL)
    {
      g_free (candidate->domain_pattern);
      g_regex_unref (candidate->domain_regex);
    }

  if (candidate->path_pattern != NULL)
    {
      g_free (candidate->path_pattern);
      g_regex_unref (candidate->path_regex);
    }

  g_object_unref (candidate->service);

  g_free (candidate);
}
