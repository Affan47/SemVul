NC_xlen_iarray(iarray)
NC_iarray *iarray ;
{
	int len = 4 ;
	if(iarray!=NULL)
	{
		len += iarray->count * 4 ;
	}
	return(len) ;
}
