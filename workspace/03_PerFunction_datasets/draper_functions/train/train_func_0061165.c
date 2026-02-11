MEMORY_CopyFromMem(UWORD from, UBYTE *to, int size)
{
	while (--size >= 0) {
		*to++ = MEMORY_GetByte(from);
		from++;
	}
}
