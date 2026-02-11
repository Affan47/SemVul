test_domain (void)
{
  const gchar buffer1[] = "<interface/>";
  const gchar buffer2[] = "<interface domain=\"domain\"/>";
  const gchar *domain;

  builder = builder_new_from_string (buffer1, -1, NULL);
  domain = gtk_builder_get_translation_domain (builder);
  cut_assert (domain == NULL);
  g_object_unref (builder);
  builder = NULL;

  builder = builder_new_from_string (buffer1, -1, "domain-1");
  domain = gtk_builder_get_translation_domain (builder);
  cut_assert (domain);
  cut_assert_equal_string ("domain-1", domain);
  g_object_unref (builder);
  builder = NULL;

  builder = builder_new_from_string (buffer2, -1, NULL);
  domain = gtk_builder_get_translation_domain (builder);
  cut_assert_equal_string (NULL, domain);
  g_object_unref (builder);
  builder = NULL;
}
