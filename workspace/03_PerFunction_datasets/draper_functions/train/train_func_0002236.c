e_contact_address_copy (EContactAddress *address)
{
	EContactAddress *address2 = g_new0 (EContactAddress, 1);

	address2->address_format = g_strdup (address->address_format);
	address2->po = g_strdup (address->po);
	address2->ext = g_strdup (address->ext);
	address2->street = g_strdup (address->street);
	address2->locality = g_strdup (address->locality);
	address2->region = g_strdup (address->region);
	address2->code = g_strdup (address->code);
	address2->country = g_strdup (address->country);

	return address2;
}
