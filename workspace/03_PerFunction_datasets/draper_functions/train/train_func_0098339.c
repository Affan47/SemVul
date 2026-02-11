SASLprep(u08bits *s)
{
	if(s) {
		u08bits *strin = s;
		u08bits *strout = s;
		for(;;) {
			u08bits c = *strin;
			if(!c) {
				*strout=0;
				break;
			}

			switch(c) {
			case 0xAD:
				++strin;
				break;
			case 0xA0:
			case 0x20:
				*strout=0x20;
				++strout;
				++strin;
				break;
			case 0x7F:
				return -1;
			default:
				if(c<0x1F)
					return -1;
				if(c>=0x80 && c<=0x9F)
					return -1;
				*strout=c;
				++strout;
				++strin;
			};
		}
	}

	return 0;
}
