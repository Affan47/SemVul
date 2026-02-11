print_sec_struct_mask(int prf_length, char *mask, char *struct_mask)
{
	int i,j;


	i=0;
	while (i<prf_length) {
		if (tolower(mask[i]) == 'a' || mask[i] == '$') {
			for (j = 0; j<helix_end_minus; j++) {
				if (i+j>=prf_length || (tolower(mask[i+j]) != 'a'
				                    && mask[i+j] != '$')) break;
				struct_mask[i+j] = 'a';
			}
			i += j;
			while (tolower(mask[i]) == 'a'
				                    || mask[i] == '$') {
				if (i>=prf_length) break;
				if (mask[i] == '$') {
					struct_mask[i] = 'A';
					i++;
					break;
				}
				else struct_mask[i] = mask[i];
				i++;
			}
			for (j = 0; j<helix_end_minus; j++) {
				if ((i-j-1>=0) && (tolower(mask[i-j-1]) == 'a'
				                    || mask[i-j-1] == '$'))
					struct_mask[i-j-1] = 'a';
			}
		}
	 	else if (tolower(mask[i]) == 'b' || mask[i] == '%') {
			for (j = 0; j<strand_end_minus; j++) {
				if (i+j>=prf_length || (tolower(mask[i+j]) != 'b'
				                    && mask[i+j] != '%')) break;
				struct_mask[i+j] = 'b';
			}
			i += j;
			while (tolower(mask[i]) == 'b'
				                    || mask[i] == '%') {
				if (i>=prf_length) break;
				if (mask[i] == '%') {
					struct_mask[i] = 'B';
					i++;
					break;
				}
				else struct_mask[i] = mask[i];
				i++;
			}
			for (j = 0; j<strand_end_minus; j++) {
				if ((i-j-1>=0) && (tolower(mask[i-j-1]) == 'b'
				                    || mask[i-j-1] == '%'))
				struct_mask[i-j-1] = 'b';
			}
		}
	else i++;
	}
}
