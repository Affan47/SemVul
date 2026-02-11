Q_strncpyz( char *dest, const char *src, size_t size )
{
	while( --size && (*dest++ = *src++) );
	*dest = '\0';
}
