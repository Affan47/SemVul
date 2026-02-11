save_att_piped(int reset)
{
    static long x;
    long	y;

    if(reset){
	x = y = 0L;
    }
    else if((y = gf_bytes_piped()) >= x){
	x = y;
	y = 0;
    }

    return(x + y);
}
