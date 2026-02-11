MEMORY_CopyToMem(const UBYTE *from, UWORD to, int size)
{
	while (--size >= 0) {
		MEMORY_PutByte(to, *from);
		from++;
		to++;
	}
}
