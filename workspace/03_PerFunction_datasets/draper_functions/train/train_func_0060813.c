bitbuffer_write_flush( bitbuffer *bitbuf )
{

	if ( bitbuf->mask != 0x80 )	{
   	*bitbuf->data++ = (ubyte)bitbuf->rack;
	}
	return bitbuf->data-bitbuf->org_data;
}
