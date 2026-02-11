get_dn_attribute_name (gchar *rootdn,
                       EContact *contact)
{


	if (strncmp (rootdn, "uid=", 4) == 0 ||
	    strstr (rootdn, ",uid=") ||
	    (contact && e_contact_get (contact, E_CONTACT_IS_LIST)))
		return "description";


	return "uid";
}
