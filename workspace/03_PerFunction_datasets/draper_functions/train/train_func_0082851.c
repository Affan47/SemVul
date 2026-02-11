unity_webapps_interest_manager_get_interest_is_active (UnityWebappsInterestManager *manager,
						       gint interest_id)
{
  UnityWebappsInterest *interest;

  interest = g_hash_table_lookup (manager->priv->interests_by_id, GINT_TO_POINTER (interest_id));

  if (interest == NULL)
    {
      return FALSE;
    }

  return interest->active;
}
