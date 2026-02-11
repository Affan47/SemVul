Mask_calcN1N3(int length, int *runLength)
{
	int i;
	int demerit = 0;
	int fact;

	for(i=0; i<length; i++) {
		if(runLength[i] >= 5) {
			demerit += N1 + (runLength[i] - 5);

		}
		if((i & 1)) {
			if(i >= 3 && i < length-2 && (runLength[i] % 3) == 0) {
				fact = runLength[i] / 3;
				if(runLength[i-2] == fact &&
				   runLength[i-1] == fact &&
				   runLength[i+1] == fact &&
				   runLength[i+2] == fact) {
					if(i == 3 || runLength[i-3] >= 4 * fact) {
						demerit += N3;

					} else if(i+4 >= length || runLength[i+3] >= 4 * fact) {
						demerit += N3;

					}
				}
			}
		}
	}

	return demerit;
}
