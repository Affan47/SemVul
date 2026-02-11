do_exec( pcredata *d, const char *str, int len, int pos ) {
	int res = pcre_exec(d->r,&limit,str,len,pos,0,d->matchs,d->nmatchs * 3);
	if( res >= 0 )
		return 1;
	if( res != PCRE_ERROR_NOMATCH )
		val_throw(alloc_string("An error occured while running pcre_exec"));
	return 0;
}
