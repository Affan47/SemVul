genbyte(int b)
{
	if( bytecount < sizeof(bytebuf) )
		bytebuf[bytecount++] = b;
	emitbyte(b);
}
