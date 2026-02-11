setup_book (EBookClient *book_client)
{
	gint   i, j;

	for (i = 0; i < N_TEST_CONTACTS; i++)
	{
		EContact *contact = e_contact_new ();
		gchar    *name = g_strdup_printf ("Contact #%d", i + 1);
		gchar    *emails[5] = {
			g_strdup_printf ("contact%d@first.email.com", i),
			g_strdup_printf ("contact%d@second.email.com", i),
			g_strdup_printf ("contact%d@third.email.com", i),
			g_strdup_printf ("contact%d@fourth.email.com", i),
			NULL
		};

		e_contact_set (contact, E_CONTACT_FULL_NAME, name);
		e_contact_set (contact, E_CONTACT_NICKNAME, name);


		for (j = E_CONTACT_EMAIL_1; j < (E_CONTACT_EMAIL_4 + 1); j++)
			e_contact_set (contact, j, emails[j - E_CONTACT_EMAIL_1]);

#if BEEFY_VCARDS

		for (j = E_CONTACT_IM_AIM_HOME_1; j < (E_CONTACT_IM_AIM_HOME_3 + 1); j++)
			e_contact_set (contact, j, emails[j - E_CONTACT_IM_AIM_HOME_1]);
		for (j = E_CONTACT_IM_AIM_WORK_1; j < (E_CONTACT_IM_AIM_WORK_3 + 1); j++)
			e_contact_set (contact, j, emails[j - E_CONTACT_IM_AIM_WORK_1]);
		for (j = E_CONTACT_IM_GROUPWISE_HOME_1; j < (E_CONTACT_IM_GROUPWISE_HOME_3 + 1); j++)
			e_contact_set (contact, j, emails[j - E_CONTACT_IM_GROUPWISE_HOME_1]);
		for (j = E_CONTACT_IM_GROUPWISE_WORK_1; j < (E_CONTACT_IM_GROUPWISE_WORK_3 + 1); j++)
			e_contact_set (contact, j, emails[j - E_CONTACT_IM_GROUPWISE_WORK_1]);
		for (j = E_CONTACT_IM_JABBER_HOME_1; j < (E_CONTACT_IM_JABBER_HOME_3 + 1); j++)
			e_contact_set (contact, j, emails[j - E_CONTACT_IM_JABBER_HOME_1]);
		for (j = E_CONTACT_IM_JABBER_WORK_1; j < (E_CONTACT_IM_JABBER_WORK_3 + 1); j++)
			e_contact_set (contact, j, emails[j - E_CONTACT_IM_JABBER_WORK_1]);
		for (j = E_CONTACT_IM_YAHOO_HOME_1; j < (E_CONTACT_IM_YAHOO_HOME_3 + 1); j++)
			e_contact_set (contact, j, emails[j - E_CONTACT_IM_YAHOO_HOME_1]);
		for (j = E_CONTACT_IM_YAHOO_WORK_1; j < (E_CONTACT_IM_YAHOO_WORK_3 + 1); j++)
			e_contact_set (contact, j, emails[j - E_CONTACT_IM_YAHOO_WORK_1]);
#endif


		if (!add_contact_verify (book_client, contact))
			g_error ("Failed to add contact");

		g_free (name);
		for (j = E_CONTACT_EMAIL_1; j < (E_CONTACT_EMAIL_4 + 1); j++)
			g_free (emails[j - E_CONTACT_EMAIL_1]);

		g_object_unref (contact);
	}

	return TRUE;
}
