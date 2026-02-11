unity_webapps_interest_manager_get_active_interest_at_window (UnityWebappsInterestManager *manager,
							      guint64 window_id)
{
  GList *interests, *walk;
  gint active_interest;

  interests = g_hash_table_get_values (manager->priv->interests_by_id);
  active_interest = -1;

  for (walk = interests; walk != NULL; walk = walk->next)
    {
      UnityWebappsInterest *interest;

      interest = (UnityWebappsInterest *)walk->data;

      if (interest->active && (interest->window == window_id))
	{
#ifdef UNITY_WEBAPPS_ENABLE_DEBUG
	  if (active_interest != -1)
	    {
	      g_warning ("Found two active interests in one window (interests %d and %d), this should not happen",
			 interest->id, active_interest);
	    }
#endif
	  active_interest = interest->id;
#ifndef UNITY_WEBAPPS_ENABLE_DEBUG
	  goto out;
#endif
	}
    }
#ifndef UNITY_WEBAPPS_ENABLE_DEBUG
 out:
#endif

  g_list_free (interests);

  return active_interest;
}
