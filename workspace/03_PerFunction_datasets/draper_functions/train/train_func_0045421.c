dump_ttl(FILE *f, const char *legend, isc_stdtime_t value, isc_stdtime_t now) {
	if (value == INT_MAX)
		return;
	fprintf(f, " [%s TTL %d]", legend, value - now);
}
