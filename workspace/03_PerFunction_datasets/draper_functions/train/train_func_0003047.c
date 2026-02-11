read(void* buffer, u32 sizeToRead)
{
	if (!isOpen())
		return 0;

	return (s32)fread(buffer, 1, sizeToRead, File);
}
