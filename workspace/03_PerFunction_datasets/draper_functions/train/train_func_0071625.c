mono_image_loaded_by_guid_full (const char *guid, gboolean refonly)
{
	GuidData data;
	GHashTable *loaded_images = refonly ? loaded_images_refonly_hash : loaded_images_hash;
	data.res = NULL;
	data.guid = guid;

	mono_images_lock ();
	g_hash_table_foreach (loaded_images, find_by_guid, &data);
	mono_images_unlock ();
	return data.res;
}
