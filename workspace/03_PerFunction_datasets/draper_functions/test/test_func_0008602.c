bio_clone(bio_file_t *bio)
{
	bio_file_t *c = malloc(sizeof(bio_file_t));
	if(!c)
		return NULL;
	*c = *bio;
	return c;
}
