BufFileLoadBuffer(BufFile *file)
{
	File		thisfile;


	if (file->curOffset >= MAX_PHYSICAL_FILESIZE &&
		file->curFile + 1 < file->numFiles)
	{
		file->curFile++;
		file->curOffset = 0L;
	}


	thisfile = file->files[file->curFile];
	if (file->curOffset != file->offsets[file->curFile])
	{
		if (FileSeek(thisfile, file->curOffset, SEEK_SET) != file->curOffset)
			return;
		file->offsets[file->curFile] = file->curOffset;
	}


	file->nbytes = FileRead(thisfile, file->buffer, sizeof(file->buffer));
	if (file->nbytes < 0)
		file->nbytes = 0;
	file->offsets[file->curFile] += file->nbytes;

}
