telex_filter_ava(
    Slapi_PBlock		*pb,
    struct berval	*bvfilter,
    Slapi_Value	**bvals,
    int			ftype,
	Slapi_Value **retVal
)
{
	int filter_normalized = 0;
	int syntax = SYNTAX_CIS;
	if (pb) {
		slapi_pblock_get( pb, SLAPI_PLUGIN_SYNTAX_FILTER_NORMALIZED,
		                  &filter_normalized );
		if (filter_normalized) {
			syntax |= SYNTAX_NORM_FILT;
		}
	}
	return( string_filter_ava( bvfilter, bvals, syntax,
							   ftype, retVal ) );
}
