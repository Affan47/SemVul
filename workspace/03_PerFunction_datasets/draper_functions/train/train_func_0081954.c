ip_chksum(unsigned short* addr, int count)
{
	unsigned short checksum;


	unsigned long sum = 0;

	while( count > 1 )  {

		   sum += *addr;
		   addr++;
		   count -= 2;
	}


	if( count > 0 )
		   sum += * (unsigned char *) addr;


	while (sum>>16)
	   sum = (sum & 0xffff) + (sum >> 16);

	checksum = ~sum;

    return checksum;
}
