yywrap()
{
	(void)fclose(yyin);
#ifdef FLEX_SCANNER

	if (csb > 0) {
		yy_delete_buffer(YY_CURRENT_BUFFER );
		yy_switch_to_buffer(rgsb[--csb] );
	}
#endif
	if (cfp > 0) {
	    yyin = rgfp[--cfp];
	    return(0);
	}
	return(1);
}
