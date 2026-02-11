sortDataPDU(u_char * buf, int len, int dir_flag)
{
    u_long pdvLength;


    len -= 6;
    buf += 6;

    do {
	memcpy((char *) &pdvLength, buf, 4);

	if (buf[5] & 0x01) {

	    printf("Command PDV fragment : Length = %u\n", pdvLength);
	    if (dir_flag == ITOA)
		parseCmdITOA(buf, pdvLength);
	    else
		parseCmdATOI(buf, pdvLength);
	} else {

	    printf("Data set PDV fragment : Length = %u\n", pdvLength);
	    if (dir_flag == ITOA)
		parseDataITOA(buf, pdvLength);
	    else
		parseDataATOI(buf, pdvLength);
	}
	buf += (pdvLength + 4);
	len = len - (int) pdvLength - 4;
    } while (len > 0);

}
