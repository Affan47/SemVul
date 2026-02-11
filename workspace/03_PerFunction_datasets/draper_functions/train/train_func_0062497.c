pcnet32_wio_read_rap ( unsigned long addr )
{
	return inw ( addr + PCNET32_WIO_RAP );
}
