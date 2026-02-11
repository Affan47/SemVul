get_contact_cb (EBook *book,
                const GError *error,
                EContact *contact,
                EBookTestClosure *closure)
{
	const gchar *uid;

	if (error) {
		g_warning (
			"failed to asynchronously get the contact: "
			"status %d (%s)", error->code, error->message);
		exit (1);
	}

	uid = e_contact_get_const (contact, E_CONTACT_UID);
	test_print (
		"successfully asynchronously retrieved the contact '%s'\n",
			uid);

	if (closure->cb)
		(*closure->cb) (closure);

	g_free (closure);
}
