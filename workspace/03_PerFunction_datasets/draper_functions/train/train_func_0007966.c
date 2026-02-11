on_view_contacts_added (GList *econtacts)
{
  EContact *econtact = NULL;
  int nbr = 0;
  gchar* c_status = NULL;

  for (; econtacts != NULL; econtacts = g_list_next (econtacts)) {

    econtact = E_CONTACT (econtacts->data);

    if (e_contact_get_const (econtact, E_CONTACT_FULL_NAME) != NULL) {

      ContactPtr contact(new Evolution::Contact (services, book,
						 econtact));

      add_contact (contact);
      nbr++;
    }
  }

  c_status = g_strdup_printf (ngettext ("%d user found", "%d users found", nbr),
			      nbr);
  status = c_status;
  g_free (c_status);

  updated ();
}
