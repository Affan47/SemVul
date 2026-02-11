e_contact_photo_set_mime_type (EContactPhoto *photo,
                               const gchar *mime_type)
{
	g_return_if_fail (photo != NULL);
	g_return_if_fail (photo->type == E_CONTACT_PHOTO_TYPE_INLINED);

	g_free (photo->data.inlined.mime_type);
	photo->data.inlined.mime_type = g_strdup (mime_type);
}
