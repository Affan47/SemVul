px_ident(PERM *px)
#endif
{
	int	i, px_size;
	unsigned int	*px_pe;

	if ( px == PNULL )
		error(E_NULL,"px_ident");

	px_size = px->size;	px_pe = px->pe;
	for ( i = 0; i < px_size; i++ )
		px_pe[i] = i;

	return px;
}
