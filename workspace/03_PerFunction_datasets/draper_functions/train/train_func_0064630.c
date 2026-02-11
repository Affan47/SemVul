internet_address_mailbox_new (const char *name, const char *addr)
{
	InternetAddressMailbox *mailbox;

	g_return_val_if_fail (addr != NULL, NULL);

	mailbox = g_object_newv (INTERNET_ADDRESS_TYPE_MAILBOX, 0, NULL);
	mailbox->addr = g_strdup (addr);

	_internet_address_set_name ((InternetAddress *) mailbox, name);

	return (InternetAddress *) mailbox;
}
