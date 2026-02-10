bio_disable(bio_source_t *bio)
{
	bio_check(bio);
	g_assert(bio->io_tag);
	g_assert(bio->io_callback);
	g_assert(0 == (bio->flags & BIO_F_PASSIVE));

	inputevt_remove(&bio->io_tag);
}
