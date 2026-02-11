iReadLump(void *Buffer, const ILuint Size, const ILuint Number)
{
	ILuint i, ByteSize = IL_MIN( Size*Number, ReadLumpSize-ReadLumpPos);

	for (i = 0; i < ByteSize; i++) {
		*((ILubyte*)Buffer + i) = *((ILubyte*)ReadLump + ReadLumpPos + i);
		if (ReadLumpSize > 0) {
			if (ReadLumpPos + i > ReadLumpSize) {
				ReadLumpPos += i;
				if (i != Number)
					ilSetError(IL_FILE_READ_ERROR);
				return i;
			}
		}
	}

	ReadLumpPos += i;
	if (Size != 0)
		i /= Size;
	if (i != Number)
		ilSetError(IL_FILE_READ_ERROR);
	return i;
}
