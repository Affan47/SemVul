endout_writeheader( FILE *outptr, param *p )
{
	if ( p->utf8bom ) utf8_writebom( outptr );
}
