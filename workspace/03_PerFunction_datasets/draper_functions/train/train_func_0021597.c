fatAppend(Fs_t *This, unsigned int pos, unsigned int newpos)
{
	This->fat_encode(This, pos, newpos);
	This->fat_encode(This, newpos, This->end_fat);
	if(This->freeSpace != MAX32)
		This->freeSpace--;
}
