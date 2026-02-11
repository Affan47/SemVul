msgno_free_exceptions(PARTEX_S **parts)
{
    if(parts && *parts){
	if((*parts)->next)
	  msgno_free_exceptions(&(*parts)->next);

	fs_give((void **) &(*parts)->partno);
	fs_give((void **) parts);
    }
}
