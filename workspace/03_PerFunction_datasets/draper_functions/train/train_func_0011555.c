pushstack( int position )
{
*stack_pointer++ = position;
if ( stack_pointer > ( stack + BZ_STACKSIZE ) ) {
	fprintf( stderr, "%s: ERROR: pushstack(): stack overflow\n", get_progname() );
	return 1;
}
return 0;
}
