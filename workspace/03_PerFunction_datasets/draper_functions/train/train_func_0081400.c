tar_flush_unconsumed(struct archive_read *a, size_t *unconsumed)
{
	if (*unconsumed) {


		__archive_read_consume(a, *unconsumed);
		*unconsumed = 0;
	}
}
