MixColumns(unsigned char *state)
{
	unsigned char tmp[StateSize];
	for(int p=0; p<NumberRows; p++){
		for(int i=0; i<NumberColumns; i++){
			for(int j=0; j<(NumberRows-1); j++)
				tmp[NumberColumns*j+i]=state[NumberColumns*(j+1)+i];
			tmp[NumberColumns*4+i]=state[i]^T18(state[NumberColumns*1+i])^T2(state[NumberColumns*2+i])^T2(state[NumberColumns*3+i])^T18(state[NumberColumns*4+i]);
		}
		for(int j=0; j<StateSize; j++)
			state[j]=tmp[j];
	}
}
