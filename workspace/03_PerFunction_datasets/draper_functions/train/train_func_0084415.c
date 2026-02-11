find_imported_account_by_uid ( gchar * guid )
{
  GSList * liste_tmp;

  if ( ! guid )
    return NULL;

  liste_tmp = gnucash_accounts;

  while ( liste_tmp )
    {
      struct struct_compte_importation * account = liste_tmp -> data;

      if ( account -> guid && !strcmp ( account -> guid, guid ))
	{
	  return account;
	}

      liste_tmp = liste_tmp -> next;
    }

  return NULL;
}
