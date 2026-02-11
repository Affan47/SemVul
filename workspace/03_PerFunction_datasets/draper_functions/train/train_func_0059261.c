e_contact_photo_get_inlined (EContactPhoto *photo,
                             gsize *len)
{
	g_return_val_if_fail (photo != NULL, NULL);
	g_return_val_if_fail (photo->type == E_CONTACT_PHOTO_TYPE_INLINED, NULL);

	*len = photo->data.inlined.length;
	return photo->data.inlined.data;
}
