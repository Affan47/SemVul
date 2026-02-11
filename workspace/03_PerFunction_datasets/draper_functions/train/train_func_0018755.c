warn( const char *msg, ... )
{
	va_list va;

	if (!(DFlags & VERYQUIET)) {
		if (need_nl) {
			putchar( '\n' );
			need_nl = 0;
		}
		va_start( va, msg );
		vfprintf( stderr, msg, va );
		va_end( va );
	}
}
