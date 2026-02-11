getormakeEContactAddress (EContact * card, EContactField field)
{
    EContactAddress *contact_addr = e_contact_get (card, field);
    if (!contact_addr)
	contact_addr = g_new0 (EContactAddress, 1);
    return contact_addr;
}
