io_in_buffer(ADAPTER *a, void *adr, void *buffer, word len)
{
	byte __iomem *Port = DIVA_OS_MEM_ATTACH_PORT((PISDN_ADAPTER)a->io);
	byte *P = (byte *)buffer;
	if ((long)adr & 1) {
		outppw(Port + 4, (word)(unsigned long)adr);
		*P = inpp(Port);
		P++;
		adr = ((byte *) adr) + 1;
		len--;
		if (!len) {
			DIVA_OS_MEM_DETACH_PORT((PISDN_ADAPTER)a->io, Port);
			return;
		}
	}
	outppw(Port + 4, (word)(unsigned long)adr);
	inppw_buffer(Port, P, len + 1);
	DIVA_OS_MEM_DETACH_PORT((PISDN_ADAPTER)a->io, Port);
}
