tm_tag_unref(TMTag *tag)
{


	if (NULL != tag && g_atomic_int_dec_and_test(&tag->refcount))
	{
		tm_tag_destroy(tag);
		TAG_FREE(tag);
	}
}
