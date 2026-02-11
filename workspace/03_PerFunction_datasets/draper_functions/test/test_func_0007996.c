in_cksum(unsigned short *ptr, int nbytes)
{
	register long sum=0;
	u_short oddbyte;

	while(nbytes>1){
        	sum+=*ptr++;
	        nbytes-=2;
	}
	if(nbytes==1){
        	oddbyte=0;
	        *(u_char *)(&oddbyte)=*(u_char *)ptr;
        	sum+=oddbyte;
	}
	sum = (sum >> 16) + (sum & 0xFFFF);
	return ~(sum  + (sum >> 16)) & 0xFFFF;
}
