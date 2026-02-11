test_lifecycle (void)
{
  DConfClient *client;
  GWeakRef weak;

  client = dconf_client_new ();
  g_weak_ref_init (&weak, client);
  g_object_unref (client);

  g_assert (g_weak_ref_get (&weak) == NULL);
  g_weak_ref_clear (&weak);
}
