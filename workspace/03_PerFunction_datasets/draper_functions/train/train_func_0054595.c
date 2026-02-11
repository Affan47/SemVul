ShiftRows(unsigned char *state)
{
	unsigned char tmp[StateSize];
	for(int j=0; j<NumberRows; j++){
		for(int i=0; i<NumberColumns; i++){
			tmp[NumberColumns*j+i]=state[NumberColumns*j+((i+shiftconst[j])%NumberColumns)];
		}
	}
	for(int j=0; j<StateSize; j++)
		state[j]=tmp[j];
}
