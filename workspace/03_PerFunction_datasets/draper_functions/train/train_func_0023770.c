e_contact_address_free (EContactAddress *address)
{
	if (!address)
		return;

	g_free (address->address_format);
	g_free (address->po);
	g_free (address->ext);
	g_free (address->street);
	g_free (address->locality);
	g_free (address->region);
	g_free (address->code);
	g_free (address->country);

	g_free (address);
}
