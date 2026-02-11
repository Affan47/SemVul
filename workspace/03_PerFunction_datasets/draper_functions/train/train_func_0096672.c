type_from_extension (const gchar *extension)
{
	g_assert (extension);

	if (strcmp (extension, ".pkcs8") == 0)
		return GKM_TYPE_GNOME2_PRIVATE_KEY;
	else if (strcmp (extension, ".pub") == 0)
		return GKM_TYPE_GNOME2_PUBLIC_KEY;
	else if (strcmp (extension, ".cer") == 0)
		return GKM_TYPE_CERTIFICATE;

	return 0;
}
