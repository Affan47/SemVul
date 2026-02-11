gtr_profile_manager_remove_profile (GtrProfileManager *manager,
                                    GtrProfile        *profile)
{
  g_return_if_fail (GTR_IS_PROFILE_MANAGER (manager));
  g_return_if_fail (profile != NULL);

  manager->priv->profiles = g_slist_remove (manager->priv->profiles,
                                            profile);

  g_signal_emit (G_OBJECT (manager), signals[PROFILE_REMOVED], 0, profile);
  g_object_unref (profile);

  save_profiles (manager);
}
