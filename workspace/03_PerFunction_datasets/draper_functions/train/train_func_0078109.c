file_cache_entry_delete (FileCacheEntry *ent)
{
	g_free (ent->filename);

	switch (ent->type) {
	case PIXBUF:
		g_object_unref (ent->u.pixbuf);
		break;
	case SLIDESHOW:
		g_object_unref (ent->u.slideshow);
		break;
	case THUMBNAIL:
		g_object_unref (ent->u.thumbnail);
		break;
	}

	g_free (ent);
}
