bio_set_favour(bio_source_t *bio, bool on)
{
	bool old;

	bio_check(bio);

	old = booleanize(bio->flags & BIO_F_FAVOUR);

	if (on) {
		bio->flags |= BIO_F_FAVOUR;
		bio->bw_allocated = 0;
	} else {
		bio->flags &= ~BIO_F_FAVOUR;
	}

	return old;
}
