destroy_studio_view(void)
{
  ASSERT(studio_loaded());

  destroy_view(g_studio_view);
  g_studio_view = NULL;
}
