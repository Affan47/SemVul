in_chain_list( ptchain, cell_name )
chain_list *ptchain;
char       *cell_name;
{
	chain_list *chainp;

	for(chainp = ptchain; chainp; chainp = chainp->NEXT)
		if ((char *)chainp->DATA == cell_name)
			return 1;

	return 0;
}
