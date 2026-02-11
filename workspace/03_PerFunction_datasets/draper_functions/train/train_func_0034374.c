GetFs(Stream_t *Fs)
{
	while(Fs && Fs->Class != &FsClass)
		Fs = Fs->Next;
	return Fs;
}
