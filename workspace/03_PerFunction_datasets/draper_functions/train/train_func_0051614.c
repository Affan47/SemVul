RunFilter(FilterEngine_data_t *args) {
uint32_t	index, offset;
int	evaluate, invert;

	index = args->StartNode;
	evaluate = 0;
	invert = 0;
	while ( index ) {
		offset   = args->filter[index].offset;
		invert   = args->filter[index].invert;
		evaluate = ( args->nfrecord[offset] & args->filter[index].mask ) == args->filter[index].value;
		index    = evaluate ?  args->filter[index].OnTrue : args->filter[index].OnFalse;
	}
	return invert ? !evaluate : evaluate;

}
