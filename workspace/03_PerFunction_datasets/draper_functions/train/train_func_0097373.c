bucket_range(const struct tally *tally, unsigned b, size_t *err)
{
	ssize_t min, max;

	min = bucket_min(tally->min, tally->step_bits, b);
	if (b == tally->buckets - 1) {
		max = tally->max;
	} else {
		max = bucket_min(tally->min, tally->step_bits, b+1) - 1;
	}


	*err = (max - min + 1) / 2;

	return min + (max - min) / 2;
}
