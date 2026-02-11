getStart(Stream_t *Dir, struct directory *dir)
{
	Stream_t *Stream = GetFs(Dir);
	unsigned int first;

	first = START(dir);
	if(fat32RootCluster(Stream))
		first |= STARTHI(dir) << 16;
	return first;
}
