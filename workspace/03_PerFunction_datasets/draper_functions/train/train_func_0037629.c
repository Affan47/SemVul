NC_arrayfill(low, len, type)
void *low ;
size_t len ;
nc_type type ;
{
	char *hi, *lo;

	lo = low;
        hi = lo + len;
	switch(type) {
	case NC_BYTE :
                HDmemset(lo, FILL_BYTE, len);
		break ;
	case NC_CHAR :
                HDmemset(lo, FILL_CHAR, len);
		break ;
	case NC_SHORT :
		while(lo < hi ){
			*((short *)lo) = FILL_SHORT ;
			lo += sizeof(short);
		}
		break ;
	case NC_LONG :
		while(lo < hi ){
			*((nclong *)lo) = FILL_LONG ;
			lo += sizeof(nclong) ;
		}
		break ;
	case NC_FLOAT :
		while(lo < hi ){
			*((float *)lo) = FILL_FLOAT ;
			lo += sizeof(float) ;
		}
		break ;
	case NC_DOUBLE :
		while(lo < hi ){

			*((double *)lo) = FILL_DOUBLE ;
			lo += sizeof(double) ;
		}
		break ;
	default :
		HDmemset(lo,0xff,len) ;
		break ;
	}
}
