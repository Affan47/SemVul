decodebyte( unsigned char opcode, unsigned short address )
{


	unsigned char xormask;


	xormask = 0;
	if (address & 0x02) xormask |= 0x80;
	else xormask |= 0x20;
	if (address & 0x08) xormask |= 0x08;
	else xormask |= 0x02;

	return opcode ^ xormask;
}
