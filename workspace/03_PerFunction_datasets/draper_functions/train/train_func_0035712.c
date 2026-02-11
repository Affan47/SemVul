_recalloc(void **ptr, size_t old, size_t new, const char *file, const char *func, const int line)
{
	if (new == old)
		return;
	*ptr = _cgrealloc(*ptr, new, file, func, line);
	if (new > old)
		memset(*ptr + old, 0, new - old);
}
