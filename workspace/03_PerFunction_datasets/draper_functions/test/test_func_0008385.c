input_huffman(unsigned char *infile)
{
int c;


	c = input_nbits(infile,3);
	if (c < 4) {


		return(1<<c);
	}


	c = input_bit(infile) | (c<<1);
	if (c < 13) {


		switch (c) {
			case  8 : return(3);
			case  9 : return(5);
			case 10 : return(10);
			case 11 : return(12);
			case 12 : return(15);
		}
	}


	c = input_bit(infile) | (c<<1);
	if (c < 31) {


		switch (c) {
			case 26 : return(6);
			case 27 : return(7);
			case 28 : return(9);
			case 29 : return(11);
			case 30 : return(13);
		}
	}


	c = input_bit(infile) | (c<<1);
	if (c == 62) {
		return(0);
	} else {
		return(14);
	}
}
