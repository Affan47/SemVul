multi_reduce_counts(int amount)
{
	Multi_sexp_bytes_left -= amount;
	current_argument_count -= amount;

	if (Multi_sexp_bytes_left < 0 || current_argument_count < 0) {
		Warning(LOCATION, "multi_get_x function call has read an invalid amount of data. Trace out and fix this!");
	}
}
