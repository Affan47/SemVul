getcolormap(nnq, map)
nn_quant *nnq;
unsigned char *map;
{
	int i,j;
	for(j=0; j < nnq->netsize; j++) {
		for (i=3; i>=0; i--) {
			*map = nnq->network[j][i];
			map++;
		}
	}
}
